<?php
namespace HTML5;

class DOM {
	public static function parse(string $html, array $options = []) : DOM\Document { }
}

namespace HTML5\DOM;

trait NonElementParentNode {
	/** @return Node|null */
	public function getElementById(string $elementId) { }
}

trait ParentNode {
	public $children; // HTMLCollection
	public $firstElementChild;
	public $lastElementChild;
	public $childElementCount;
	
	public function getElementsByTagName(string $qualifiedName) : HTMLCollection { }
	public function getElementsByTagNameNS(string $namespace, string $localName) : HTMLCollection { }
	public function getElementsByClassName(string $classNames) : HTMLCollection { }
	
	/** @param Node|string ...$nodes */
	public function prepend(...$nodes) : void { }
	
	/** @param Node|string ...$nodes */
	public function append(...$nodes) : void { }
	
	/** @return Node|null */
	public function querySelector(string $selectors) : Node { }
	
	public function querySelectorAll(string $selectors) : NodeList { }
}

trait ChildNode {
	/** @param Node|string ...$nodes */
	public function before(...$nodes) : void { }
	
	/** @param Node|string ...$nodes */
	public function after(...$nodes) : void { }
	
	/** @param Node|string ...$nodes */
	public function replaceWith(...$nodes) : void { }
	
	public function remove() : void { }
}

trait NonDocumentTypeChildNode {
	public $previousElementSibling;
	public $nextElementSibling;
}

trait DocumentNonStandart {
	public function getParseErrors() : array { }
}

class Parser {
	private function __construct($options = []) { }
	public function parse(string $html, array $options = []) : DOM\Document { }
}

class StreamParser {
	private function __construct($options = []) { }
	public function begin(array $options = []) : DOM\Document { }
	public function parse(string $html) : void { }
	public function end() : void { }
}

class DOMException extends \Exception {
	const UNKNOWN_ERROR					= 0; // non-standart
	const INDEX_SIZE_ERR				= 1;
	const DOMSTRING_SIZE_ERR			= 2;
	const HIERARCHY_REQUEST_ERR			= 3;
	const WRONG_DOCUMENT_ERR			= 4;
	const INVALID_CHARACTER_ERR			= 5;
	const NO_DATA_ALLOWED_ERR			= 6;
	const NO_MODIFICATION_ALLOWED_ERR	= 7;
	const NOT_FOUND_ERR					= 8;
	const NOT_SUPPORTED_ERR				= 9;
	const INUSE_ATTRIBUTE_ERR			= 10;

	// Introduced in DOM Level 2:
	const INVALID_STATE_ERR				= 11;

	// Introduced in DOM Level 2:
	const SYNTAX_ERR					= 12;

	// Introduced in DOM Level 2:
	const INVALID_MODIFICATION_ERR		= 13;

	// Introduced in DOM Level 2:
	const NAMESPACE_ERR					= 14;

	// Introduced in DOM Level 2:
	const INVALID_ACCESS_ERR			= 15;

	// Introduced in DOM Level 3:
	const VALIDATION_ERR				= 16;

	// Introduced in DOM Level 3:
	const TYPE_MISMATCH_ERR				= 17;

	// Introduced as an XHR extension:
	const SECURITY_ERR					= 18;

	// Introduced in HTML5:
	const NETWORK_ERR					= 19;
	const ABORT_ERR						= 20;
	const URL_MISMATCH_ERR				= 21;
	const QUOTA_EXCEEDED_ERR			= 22;

	// TIMEOUT_ERR is currently unused but was added for completeness.
	const TIMEOUT_ERR					= 23;

	// INVALID_NODE_TYPE_ERR is currently unused but was added for completeness.
	const INVALID_NODE_TYPE_ERR			= 24;
	const DATA_CLONE_ERR				= 25;
}

class EventTarget {
	private function __construct() { }
}

class Node extends EventTarget {
	const ELEMENT_NODE					= 1;
	const ATTRIBUTE_NODE				= 2;
	const TEXT_NODE						= 3;
	const CDATA_SECTION_NODE			= 4;
	const ENTITY_REFERENCE_NODE			= 5; // historical
	const ENTITY_NODE					= 6; // historical
	const PROCESSING_INSTRUCTION_NODE	= 7;
	const COMMENT_NODE					= 8;
	const DOCUMENT_NODE					= 9;
	const DOCUMENT_TYPE_NODE			= 10;
	const DOCUMENT_FRAGMENT_NODE		= 11;
	const NOTATION_NODE					= 12; // historical
	
	const DOCUMENT_POSITION_DISCONNECTED			= 0x01;
	const DOCUMENT_POSITION_PRECEDING				= 0x02;
	const DOCUMENT_POSITION_FOLLOWING				= 0x04;
	const DOCUMENT_POSITION_CONTAINS				= 0x08;
	const DOCUMENT_POSITION_CONTAINED_BY			= 0x10;
	const DOCUMENT_POSITION_IMPLEMENTATION_SPECIFIC	= 0x20;
	
	public $nodeType;
	public $nodeName;
	public $baseURI;
	public $isConnected;
	public $ownerDocument;
	public $parentNode;
	public $parentElement;
	public $childNodes;
	public $firstChild;
	public $lastChild;
	public $previousSibling;
	public $nextSibling;
	public $nodeValue;
	public $textContent;
	
	public $private;
	
	public function getRootNode(array $options = []) : Node { }
	public function hasChildNodes() : bool { }
	public function normalize() : void { }
	public function cloneNode(bool $deep = false) : Node { }
	
	/** @param Node|null ...$otherNode */
	public function isEqualNode(Node $otherNode) : bool { }
	
	/** @param Node|null ...$otherNode */
	public function isSameNode(Node $otherNode) : bool { }
	
	public function compareDocumentPosition(Node $other) : int { }
	
	/** @param Node|null ...$other */
	public function contains(Node $other) : bool { }
	
	/** @param Node|null ...$child */
	public function insertBefore(Node $node, Node $child) : Node { }
	
	public function appendChild(Node $child) : Node { }
	
	public function replaceChild(Node $node, Node $child) : Node { }
	
	public function removeChild(Node $child) : Node { }
}

class Document extends Node {
	use ParentNode;
	use NonElementParentNode;
	use DocumentNonStandart;
	
	public $URL; // about:blank
	public $documentURI; // about:blank
	public $origin; // null
	
	public $compatMode;
	public $characterSet;
	public $charset; // historical alias of .characterSet
	public $inputEncoding; // historical alias of .characterSet
	public $contentType;
	
	public $doctype; // DocumentType
	public $documentElement;
	
	public function createElement(string $localName) : Element { }
	
	public function createElementNS(string $namespace, string $qualifiedName) : Element { }
	public function createDocumentFragment() : DocumentFragment { }
	public function createTextNode(string $data) : Text { }
	public function createComment(string $data) : Comment { }
	public function createCDATASection(string $data) : CDATASection { }
	public function createProcessingInstruction(string $target, string $data) : ProcessingInstruction { }
	
	public function importNode(Node $node, bool $deep = false) : Node { }
	public function adoptNode(Node $data) : Node { }
	
	public function createAttribute(string $localName) : Attr { }
	public function createAttributeNS(string $namespace, string $localName) : Attr { }
}

class DocumentFragment extends Node {
	use ParentNode;
	use NonElementParentNode;
}

class DocumentType {
	use ChildNode;
	
	public $name;
	public $publicId;
	public $systemId;
}

class Attr extends Node {
	public $namespaceURI;
	public $prefix;
	public $localName;
	
	public $name;
	public $value;
	public $ownerElement;
}

class CharacterData extends Node {
	use ChildNode;
	use NonDocumentTypeChildNode;
	
	public $data;
	public $length;
	
	public function substringData(int $offset, int $count) : string { }
	public function appendData(string $data) : void { }
	public function insertData(int $offset, string $data) : void { }
	public function deleteData(int $offset, int $count) : void { }
	public function replaceData(int $offset, int $count, string $data) : void { }
}

class Text extends CharacterData {
	use ChildNode;
	
	public $wholeText;
	
	public function splitText(int $offset) : Text { }
}

class CDATASection extends Text {
	
}

class Comment extends CharacterData {
	
}

class ProcessingInstruction extends CharacterData {
	public $target;
}

class Element extends Node {
	use ParentNode;
	use NonDocumentTypeChildNode;
	
	public $namespaceURI; // ns uri
	public $prefix; // ns
	public $localName; // element
	public $tagName; // ns:element
	
	public $id;
	public $className;
	public $classList; // DOMTokenList
	public $attributes; // NamedNodeMap
	
	public $innerHTML;
	public $outerHTML;
	
	public function hasAttributes() : bool { }
	public function getAttributeNames() : array { }
	
	/** @return string|null */
	public function getAttribute(string $qualifiedName) : string { }
	
	/** @return string|null */
	public function getAttributeNS(string $namespace, string $localName) : string { }
	
	public function setAttribute(string $qualifiedName, string $value) : void { }
	public function setAttributeNS(string $namespace, string $localName, string $value) : void { }
	
	public function removeAttribute(string $qualifiedName) : void { }
	public function removeAttributeNS(string $namespace, string $localName) : void { }
	
	public function toggleAttribute(string $qualifiedName, bool $force = NULL) : bool { }
	public function toggleAttributeNS(string $namespace, string $localName, bool $force = NULL) : bool { }
	
	public function hasAttribute(string $qualifiedName) : bool { }
	public function hasAttributeNS(string $namespace, string $localName) : bool { }
	
	/** @return Attr|null */
	public function getAttributeNode(string $qualifiedName) : Attr { }
	
	/** @return Attr|null */
	public function getAttributeNodeNS(string $namespace, string $localName) : Attr { }
	
	/** @return Attr|null */
	public function setAttributeNode(Attr $attr) : Attr { }
	
	/** @return Attr|null */
	public function setAttributeNodeNS(Attr $attr) : Attr { }
	
	public function removeAttributeNode(Attr $attr) : Attr { }
	
	/** @return Node|null */
	public function closest($selectors) : Node { }
	
	public function matches($selectors) : bool { }
	
	/** @return Node|null */
	public function insertAdjacentElement(string $where, Node $element) : Node { } // historical
	
	public function insertAdjacentText(string $where, string $data) : void { } // historical
	
	public function insertAdjacentHTML(string $where, string $html) : void { } // historical
}

class HTMLCollection implements \Iterator, \ArrayAccess, \Countable {
	public $length;
	
	/** @return Node|null */
	public function item(int $index) : Node { }
	
	/** @return Node|null */
	public function namedItem(string $name) : Node { }
	
	/*
	 * Iterator
	 */
	public function current() { }
	
	public function key() { }
	
	public function next() { }
	
	public function rewind() { }
	
	public function valid() { }
	
	/*
	 * ArrayAccess
	 */
	public function offsetExists($offset) { }
	
	public function offsetGet($offset) { }
	
	public function offsetSet($offset, $value) { }
	
	public function offsetUnset($offset) { }
	
	/*
	 * Countable
	 */
	public function count() { }
}

class NodeList implements \Iterator, \ArrayAccess, \Countable {
	public $length;
	
	/** @return Node|null */
	public function item(int $index) : Node { }
	
	/*
	 * Iterator
	 */
	public function current() { }
	
	public function key() { }
	
	public function next() { }
	
	public function rewind() { }
	
	public function valid() { }
	
	/*
	 * ArrayAccess
	 */
	public function offsetExists($offset) { }
	
	public function offsetGet($offset) { }
	
	public function offsetSet($offset, $value) { }
	
	public function offsetUnset($offset) { }
	
	/*
	 * Countable
	 */
	public function count() { }
}

class DOMTokenList implements \Iterator, \ArrayAccess, \Countable {
	public $length;
	public $value;
	
	/** @return string|null */
	public function item(int $index) : string { }
	
	public function contains(string $token) : bool { }
	
	public function add(string ...$tokens) : void { }
	
	public function remove(string ...$tokens) : void { }
	
	public function toggle(string $token, bool $force = NULL) : bool { }
	
	public function replace(string $token, string $newToken) : bool { }
	
	public function supports(string $token) : bool { }
	
	/*
	 * Iterator
	 */
	public function current() { }
	
	public function key() { }
	
	public function next() { }
	
	public function rewind() { }
	
	public function valid() { }
	
	/*
	 * ArrayAccess
	 */
	public function offsetExists($offset) { }
	
	public function offsetGet($offset) { }
	
	public function offsetSet($offset, $value) { }
	
	public function offsetUnset($offset) { }
	
	/*
	 * Countable
	 */
	public function count() { }
}

class NamedNodeMap implements \Iterator, \ArrayAccess, \Countable {
	public $length;
	public $value;
	
	/** @return Attr|null */
	public function item(int $index) : Attr { }
	
	/** @return Attr|null */
	public function getNamedItem(string $qualifiedName) : Attr { }
	
	/** @return Attr|null */
	public function getNamedItemNS(string $namespace, string $localName) : Attr { }
	
	/** @return Attr|null */
	public function setNamedItem(Attr $attr) : Attr { }
	
	/** @return Attr|null */
	public function setNamedItemNS(Attr $attr) : Attr { }
	
	public function removeNamedItem(string $qualifiedName) : Attr { }
	
	public function removeNamedItemNS(string $namespace, string $localName) : Attr { }
	
	/*
	 * Iterator
	 */
	public function current() { }
	
	public function key() { }
	
	public function next() { }
	
	public function rewind() { }
	
	public function valid() { }
	
	/*
	 * ArrayAccess
	 */
	public function offsetExists($offset) { }
	
	public function offsetGet($offset) { }
	
	public function offsetSet($offset, $value) { }
	
	public function offsetUnset($offset) { }
	
	/*
	 * Countable
	 */
	public function count() { }
}
