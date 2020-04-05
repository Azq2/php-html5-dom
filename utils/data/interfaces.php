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
	/** @var HTMLCollection|readonly */
	public $children;
	
	/** @var Element|null|readonly */
	public $firstElementChild;
	
	/** @var Element|null|readonly */
	public $lastElementChild;
	
	/** @var int|readonly */
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
	/** @var Element|null|readonly */
	public $previousElementSibling;
	
	/** @var Element|null|readonly */
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
	/** @const LXB_DOM_INDEX_SIZE_ERR */
	const INDEX_SIZE_ERR				= 1;
	
	/** @const LXB_DOM_DOMSTRING_SIZE_ERR */
	const DOMSTRING_SIZE_ERR			= 2;
	
	/** @const LXB_DOM_HIERARCHY_REQUEST_ERR */
	const HIERARCHY_REQUEST_ERR			= 3;
	
	/** @const LXB_DOM_WRONG_DOCUMENT_ERR */
	const WRONG_DOCUMENT_ERR			= 4;
	
	/** @const LXB_DOM_INVALID_CHARACTER_ERR */
	const INVALID_CHARACTER_ERR			= 5;
	
	/** @const LXB_DOM_NO_DATA_ALLOWED_ERR */
	const NO_DATA_ALLOWED_ERR			= 6;
	
	/** @const LXB_DOM_NO_MODIFICATION_ALLOWED_ERR */
	const NO_MODIFICATION_ALLOWED_ERR	= 7;
	
	/** @const LXB_DOM_NOT_FOUND_ERR */
	const NOT_FOUND_ERR					= 8;
	
	/** @const LXB_DOM_NOT_SUPPORTED_ERR */
	const NOT_SUPPORTED_ERR				= 9;
	
	/** @const LXB_DOM_INUSE_ATTRIBUTE_ERR */
	const INUSE_ATTRIBUTE_ERR			= 10;
	
	/** @const LXB_DOM_INVALID_STATE_ERR */
	const INVALID_STATE_ERR				= 11;
	
	/** @const LXB_DOM_SYNTAX_ERR */
	const SYNTAX_ERR					= 12;
	
	/** @const LXB_DOM_INVALID_MODIFICATION_ERR */
	const INVALID_MODIFICATION_ERR		= 13;
	
	/** @const LXB_DOM_NAMESPACE_ERR */
	const NAMESPACE_ERR					= 14;
	
	/** @const LXB_DOM_INVALID_ACCESS_ERR */
	const INVALID_ACCESS_ERR			= 15;
	
	/** @const LXB_DOM_VALIDATION_ERR */
	const VALIDATION_ERR				= 16;
	
	/** @const LXB_DOM_TYPE_MISMATCH_ERR */
	const TYPE_MISMATCH_ERR				= 17;
	
	/** @const LXB_DOM_SECURITY_ERR */
	const SECURITY_ERR					= 18;
	
	/** @const LXB_DOM_NETWORK_ERR */
	const NETWORK_ERR					= 19;
	
	/** @const LXB_DOM_ABORT_ERR */
	const ABORT_ERR						= 20;
	
	/** @const LXB_DOM_URL_MISMATCH_ERR */
	const URL_MISMATCH_ERR				= 21;
	
	/** @const LXB_DOM_QUOTA_EXCEEDED_ERR */
	const QUOTA_EXCEEDED_ERR			= 22;
	
	/** @const LXB_DOM_TIMEOUT_ERR */
	const TIMEOUT_ERR					= 23;
	
	/** @const LXB_DOM_INVALID_NODE_TYPE_ERR */
	const INVALID_NODE_TYPE_ERR			= 24;
	
	/** @const LXB_DOM_DATA_CLONE_ERR */
	const DATA_CLONE_ERR				= 25;
	
	/** @var string|readonly */
	public $name;
	
	/** @var string|readonly */
	public $message;
	
	/** @var int|readonly */
	public $code;
	
	public function __construct(string $message = '', string $name = '') { }
}

class EventTarget {
	private function __construct() { }
}

class Node extends EventTarget {
	/** @const LXB_DOM_NODE_TYPE_ELEMENT */
	const ELEMENT_NODE					= 1;
	
	/** @const LXB_DOM_NODE_TYPE_ATTRIBUTE */
	const ATTRIBUTE_NODE				= 2;
	
	/** @const LXB_DOM_NODE_TYPE_TEXT */
	const TEXT_NODE						= 3;
	
	/** @const LXB_DOM_NODE_TYPE_CDATA_SECTION */
	const CDATA_SECTION_NODE			= 4;
	
	/** @const LXB_DOM_NODE_TYPE_ENTITY_REFERENCE */
	const ENTITY_REFERENCE_NODE			= 5; // historical
	
	/** @const LXB_DOM_NODE_TYPE_ENTITY */
	const ENTITY_NODE					= 6; // historical
	
	/** @const LXB_DOM_NODE_TYPE_PROCESSING_INSTRUCTION */
	const PROCESSING_INSTRUCTION_NODE	= 7;
	
	/** @const LXB_DOM_NODE_TYPE_COMMENT */
	const COMMENT_NODE					= 8;
	
	/** @const LXB_DOM_NODE_TYPE_DOCUMENT */
	const DOCUMENT_NODE					= 9;
	
	/** @const LXB_DOM_NODE_TYPE_DOCUMENT_TYPE */
	const DOCUMENT_TYPE_NODE			= 10;
	
	/** @const LXB_DOM_NODE_TYPE_DOCUMENT_FRAGMENT */
	const DOCUMENT_FRAGMENT_NODE		= 11;
	
	/** @const LXB_DOM_NODE_TYPE_NOTATION */
	const NOTATION_NODE					= 12; // historical
	
	const DOCUMENT_POSITION_DISCONNECTED			= 0x01;
	const DOCUMENT_POSITION_PRECEDING				= 0x02;
	const DOCUMENT_POSITION_FOLLOWING				= 0x04;
	const DOCUMENT_POSITION_CONTAINS				= 0x08;
	const DOCUMENT_POSITION_CONTAINED_BY			= 0x10;
	const DOCUMENT_POSITION_IMPLEMENTATION_SPECIFIC	= 0x20;
	
	/** @var int|readonly */
	public $nodeType;
	
	/** @var string|readonly */
	public $nodeName;
	
	/** @var string|null|readonly */
	public $baseURI;
	
	/** @var bool|readonly */
	public $isConnected;
	
	/** @var Document|null|readonly */
	public $ownerDocument;
	
	/** @var Node|null|readonly */
	public $parentNode;
	
	/** @var Element|null|readonly */
	public $parentElement;
	
	/** @var NodeList|readonly */
	public $childNodes;
	
	/** @var Node|null|readonly */
	public $firstChild;
	
	/** @var Node|null|readonly */
	public $lastChild;
	
	/** @var Node|null|readonly */
	public $previousSibling;
	
	/** @var Node|null|readonly */
	public $nextSibling;
	
	/** @var string|null|readonly */
	public $nodeValue;
	
	/** @var string|null|readonly */
	public $textContent;
	
	/** @var mixed */
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
	
	/** @var string|readonly */
	public $URL; // about:blank
	
	/** @var string|readonly */
	public $documentURI; // about:blank
	
	/** @var string|null|readonly */
	public $origin; // null
	
	/** @var string|readonly */
	public $compatMode;
	
	/** @var string|readonly */
	public $characterSet;
	
	/** @var string|readonly */
	public $charset; // historical alias of .characterSet
	
	/** @var string|readonly */
	public $inputEncoding; // historical alias of .characterSet
	
	/** @var string|readonly */
	public $contentType;
	
	/** @var DocumentType|null|readonly */
	public $doctype;
	
	/** @var Element|null|readonly */
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
	
	/** @var string|readonly */
	public $name;
	
	/** @var string|readonly */
	public $publicId;
	
	/** @var string|readonly */
	public $systemId;
}

class Attr extends Node {
	/** @var string|null|readonly */
	public $namespaceURI;
	
	/** @var string|null|readonly */
	public $prefix;
	
	/** @var string|readonly */
	public $localName;
	
	/** @var string|readonly */
	public $name;
	
	/** @var string */
	public $value;
	
	/** @var Element|null|readonly */
	public $ownerElement;
}

class CharacterData extends Node {
	use ChildNode;
	use NonDocumentTypeChildNode;
	
	/** @var string */
	public $data;
	
	/** @var int|readonly */
	public $length;
	
	public function substringData(int $offset, int $count) : string { }
	public function appendData(string $data) : void { }
	public function insertData(int $offset, string $data) : void { }
	public function deleteData(int $offset, int $count) : void { }
	public function replaceData(int $offset, int $count, string $data) : void { }
}

class Text extends CharacterData {
	use ChildNode;
	
	/** @var string|readonly */
	public $wholeText;
	
	public function splitText(int $offset) : Text { }
}

class CDATASection extends Text {
	
}

class Comment extends CharacterData {
	
}

class ProcessingInstruction extends CharacterData {
	/** @var string|readonly */
	public $target;
}

class Element extends Node {
	use ParentNode;
	use NonDocumentTypeChildNode;
	
	/** @var string|null|readonly */
	public $namespaceURI; // ns uri
	
	/** @var string|null|readonly */
	public $prefix; // ns
	
	/** @var string|readonly */
	public $localName; // element
	
	/** @var string|readonly */
	public $tagName; // ns:element
	
	/** @var string */
	public $id;
	
	/** @var string */
	public $className;
	
	/** @var DOMTokenList|readonly */
	public $classList; // DOMTokenList
	
	/** @var NamedNodeMap|readonly */
	public $attributes; // NamedNodeMap
	
	/** @var string */
	public $innerHTML;
	
	/** @var string */
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
	/** @var int|readonly */
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
	/** @var int|readonly */
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
	/** @var int|readonly */
	public $length;
	
	/** @var string */
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
	/** @var int|readonly */
	public $length;
	
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
