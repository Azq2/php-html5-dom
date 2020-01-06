<?php
$root = realpath(__DIR__."/../");

require __DIR__."/data/interfaces.php";

$tpl_params = [
	'classes'		=> [],		// classes
	'all_classes'	=> []		// classes + traits
];

foreach (array_merge(get_declared_classes(), get_declared_traits()) as $class) {
	if (strpos($class, "HTML5\\DOM") !== 0)
		continue;
	
	$class_info = getClassInfo($class);
	
	if (!$class_info['is_trait'])
		$tpl_params['classes'][] = $class_info;
	
	$tpl_params['all_classes'][] = $class_info;
}

file_put_contents($root.'/src/php7/interfaces.c', tpl(__DIR__.'/data/interfaces_php7.c', $tpl_params));
file_put_contents($root.'/src/php7/interfaces.h', tpl(__DIR__.'/data/interfaces_php7.h', $tpl_params));

function tpl($___name, $___params) {
	extract($___params);
	ob_start();
	require $___name;
	return ob_get_clean();
}

function getClassInfo($class) {
	$ref_class = new ReflectionClass($class);
	$ref_class_parent = $ref_class->getParentClass();
	
	$class_info = [
		'name'			=> $class, 
		'id'			=> strtolower(str_replace("\\", "_", $class)), 
		'prefix'		=> str_replace("\\", "_", $class), 
		'props'			=> [], 
		'own_props'		=> [], 
		'methods'		=> [], 
		'own_methods'	=> [], 
		'parents'		=> [], 
		'consts'		=> [], 
		'is_trait'		=> $ref_class->isTrait()
	];
	
	// Get properties and methods inherited from traits
	$trait_methods = [];
	$trait_props = [];
	
	foreach ($ref_class->getTraits() as $trait) {
		foreach ($trait->getProperties() as $prop)
			$trait_props[$prop->getName()] = getClassInfo($trait->getName());
		
		foreach ($trait->getMethods() as $method)
			$trait_methods[$method->getName()] = getClassInfo($trait->getName());
	}
	
	// Get own class constants
	foreach ($ref_class->getConstants() as $k => $v) {
		if (!$ref_class_parent || !$ref_class_parent->hasConstant($k)) {
			$class_info['consts'][] = [
				'name'	=> $k, 
				'value'	=> $v
			];
		}
	}
	
	// Get class parents
	$cursor = $ref_class_parent;
	while ($cursor) {
		if (strpos($cursor->getName(), "HTML5\\DOM") !== 0)
			break;
		
		$class_info['parents'][] = getClassInfo($cursor->getName());
		$cursor = $cursor->getParentClass();
	}
	
	// Get own class properties
	foreach ($ref_class->getProperties() as $prop) {
		if (!$ref_class_parent || !$ref_class_parent->hasProperty($prop->getName())) {
			$property_class = $trait_props[$prop->getName()] ?? $class_info;
			
			$property_info = [
				'name'		=> $prop->getName(), 
				'prefix'	=> $property_class['id']
			];
			
			if ($property_class['name'] == $class_info['name'])
				$class_info['own_props'][] = $property_info;
			
			$class_info['props'][] = $property_info;
		}
	}
	
	foreach ($ref_class->getMethods() as $method) {
		if (!$ref_class_parent || !$ref_class_parent->hasMethod($method->getName())) {
			$method_class = $trait_methods[$method->getName()] ?? $class_info;
			
			$modifiers = [];
			
			if ($method->isFinal())
				$modifiers[] = "ZEND_ACC_FINAL";
			
			if ($method->isPrivate())
				$modifiers[] = "ZEND_ACC_PRIVATE";
			
			if ($method->isProtected())
				$modifiers[] = "ZEND_ACC_PROTECTED";
			
			if ($method->isStatic())
				$modifiers[] = "ZEND_ACC_STATIC";
			
			if ($method->isPublic())
				$modifiers[] = "ZEND_ACC_PUBLIC";
			
			if ($method->isConstructor())
				$modifiers[] = "ZEND_ACC_CTOR";
			
			if ($method->isDestructor())
				$modifiers[] = "ZEND_ACC_DTOR";
			
			$method_info = [
				'name'			=> $method->getName(), 
				'prefix'		=> $method_class['prefix'], 
				'required'		=> $method->getNumberOfRequiredParameters(), 
				'arginfo'		=> [], 
				'hint'			=> getTypeHint($method), 
				'modifiers'		=> implode(" | ", $modifiers)
			];
			
			foreach ($method->getParameters() as $param) {
				$method_info['arginfo'][] = [
					'name'		=> $param->getName(), 
					'hint'		=> getTypeHint($param, $method), 
				];
			}
			
			if ($method_class['name'] == $class_info['name'])
				$class_info['own_methods'][] = $method_info;
			
			$class_info['methods'][] = $method_info;
		}
	}
	
	return $class_info;
}

function getTypeHint($obj, $parent = false) {
	$builtin_types = [
		'int'			=> 'IS_LONG', 
		'string'		=> 'IS_STRING', 
		'float'			=> 'IS_DOUBLE', 
		'double'		=> 'IS_DOUBLE', 
		'bool'			=> '_IS_BOOL', 
		'array'			=> 'IS_ARRAY', 
		'object'		=> 'IS_OBJECT', 
		'void'			=> 'IS_VOID'
	];
	
	$hint = [
		'type'		=> 'none', 
		'value'		=> false, 
		'null'		=> false
	];
	
	$type_name = false;
	
	if (($obj instanceof ReflectionMethod)) {
		if ($obj->hasReturnType()) {
			$type_name = $obj->getReturnType()->getName();
			if ($obj->getReturnType()->allowsNull())
				$hint['null'] = true;
		}
		
		$hint['ref'] = $obj->returnsReference();
		
		$doc = $obj->getDocComment();
		if (preg_match("/\@return\s+([^\s]+)/", $doc, $m)) {
			$types = explode("|", $m[1]);
			$hint['null'] = in_array("null", $types);
		}
	} elseif (($obj instanceof ReflectionParameter)) {
		if ($obj->hasType()) {
			$type_name = $obj->getType()->getName();
			if ($obj->getType()->allowsNull())
				$hint['null'] = true;
		}
		
		$hint['variadic'] = $obj->isVariadic();
		$hint['ref'] = $obj->isPassedByReference();
		
		if ($obj->allowsNull())
			$hint['null'] = true;
		
		$doc = $parent->getDocComment();
		if (preg_match("/\@param\s+([^\s]+)\s+".preg_quote(($obj->isVariadic() ? "...$" : "$").$obj->getName())."/", $doc, $m)) {
			$types = explode("|", $m[1]);
			$hint['null'] = in_array("null", $types);
		}
	}
	
	if ($type_name) {
		if (isset($builtin_types[$type_name])) {
			$hint['type'] = 'type_info';
			$hint['value'] = $builtin_types[$type_name];
		} else {
			$hint['type'] = 'obj_info';
			$hint['value'] = $type_name;
		}
	}
	
	return $hint;
}
