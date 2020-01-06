<?php
$root = realpath(__DIR__."/../");

require __DIR__."/data/interfaces.php";

$tpl_params = [];

foreach (get_declared_classes() as $class) {
	if (strpos($class, "HTML5\\DOM") !== 0)
		continue;
	
	$ce_info = [
		'name'		=> $class, 
		'id'		=> strtolower(str_replace("\\", "_", $class)), 
		'prefix'	=> str_replace("\\", "_", $class), 
		'props'		=> [], 
		'methods'	=> [], 
		'const'		=> []
	];
	
	$ref_class = new ReflectionClass($class);
	
	$ref_class_parent = $ref_class->getParentClass();
	
	// echo "$class".($ref_class_parent ? " extends ".$ref_class_parent->getName() : "")."\n";
	
	foreach ($ref_class->getConstants() as $k => $v) {
		if (!$ref_class_parent || !$ref_class_parent->hasConstant($k)) {
			$ce_info['const'][] = [
				'name'	=> $k, 
				'value'	=> $v
			];
		}
	}
	
	foreach ($ref_class->getProperties() as $prop) {
		if (!$ref_class_parent || !$ref_class_parent->hasProperty($prop->getName())) {
			// echo "\t$".$prop->getName()."\n";
			$ce_info['props'][] = $prop->getName();
		}
	}
	
	foreach ($ref_class->getMethods() as $method) {
		if (!$ref_class_parent || !$ref_class_parent->hasMethod($method->getName())) {
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
			
			$ce_info['methods'][] = $method_info;
			
			/*
			$params = array_map(function ($v) {
				return $v->getName();
			}, $method->getParameters());
			
			for ($i = 0; $i < count($params); ++$i) {
				if ($i + 1 > $method->getNumberOfRequiredParameters())
					$params[$i] = "[".$params[$i];
				
				if ($i + 1 > $method->getNumberOfRequiredParameters() && ($i + 1) == count($params))
					$params[$i] = $params[$i]."]";
			}
			
			echo "\t".$method->getName()."(".implode(", ", $params).")\n";
			*/
		}
	}
	
	$tpl_params['classes'][] = $ce_info;
}

file_put_contents($root.'/src/php7/interfaces.c', tpl(__DIR__.'/data/interfaces_php7.c', $tpl_params));
file_put_contents($root.'/src/php7/interfaces.h', tpl(__DIR__.'/data/interfaces_php7.h', $tpl_params));

function tpl($___name, $___params) {
	extract($___params);
	ob_start();
	require $___name;
	return ob_get_clean();
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
