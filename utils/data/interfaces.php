<?php
namespace HTML5;

abstract class DOM {
	public abstract function __construct(array $options = []);
	public abstract function parse(string $html, array $options = []) : DOM\Document;
	public abstract function parseChunkStart(string $html, array $options = []) : DOM;
	public abstract function parseChunk(string $html) : DOM;
	public abstract function parseChunkResult() : DOM\Document;
	public abstract function parseChunkEnd() : DOM\Document;
	public abstract function parseAsync(string $html, bool $loop = false, bool $callback = false) : DOM\AsyncResult;
}

namespace HTML5\DOM;

trait NonElementParentNode {
	public abstract function getElementById(string $elementId) : Node;
}

trait ParentNode {
	public $children; // HTMLCollection
	public $firstElementChild;
	public $lastElementChild;
	public $childElementCount;
	
	public abstract function getElementsByTagName(string $qualifiedName) : HTMLCollection;
	public abstract function getElementsByTagNameNS(string $namespace, string $localName) : HTMLCollection;
	public abstract function getElementsByClassName(string $classNames) : HTMLCollection;
	
	public abstract function prepend(...$nodes) : void;
	public abstract function append(...$nodes) : void;
	
	public abstract function querySelector($selectors) : Node;
	public abstract function querySelectorAll($selectors) : NodeList;
}

trait ChildNode {
	public abstract function before(...$nodes) : void;
	public abstract function after(...$nodes) : void;
	public abstract function replaceWith(...$nodes) : void;
	public abstract function remove() : void;
}

trait NonDocumentTypeChildNode {
	public $previousElementSibling;
	public $nextElementSibling;
}

abstract class AsyncResult {
	public $done;
	public abstract function fd() : int;
	public abstract function wait() : Document;
}

abstract class EventTarget {
	
}

abstract class Node extends EventTarget {
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
	
	public abstract function getRootNode() : Node;
	public abstract function hasChildNodes() : bool;
	public abstract function normalize() : void;
	public abstract function cloneNode(bool $deep = false) : Node;
	public abstract function isEqualNode(Node $otherNode) : bool;
	public abstract function isSameNode(Node $otherNode) : bool;
	public abstract function compareDocumentPosition(Node $other) : int;
	public abstract function contains(Node $other) : bool;
	
	public abstract function insertBefore(Node $node, Node $child) : Node;
	public abstract function appendChild(Node $child) : Node;
	public abstract function replaceChild(Node $node, Node $child) : Node;
	public abstract function removeChild(Node $child) : Node;
}

abstract class Document extends Node {
	use ParentNode;
	use NonElementParentNode;
	
	public $URL;
	public $documentURI;
	public $origin;
	
	public $compatMode;
	public $characterSet;
	public $charset; // historical alias of .characterSet
	public $inputEncoding; // historical alias of .characterSet
	public $contentType;
	
	public $doctype; // DocumentType
	public $documentElement;
	
	public abstract function createElement(string $localName);
	public abstract function createElementNS(string $namespace, string $qualifiedName);
	
	public abstract function createDocumentFragment() : DocumentFragment;
	public abstract function createTextNode(string $data) : Text;
	public abstract function createComment(string $data) : Comment;
	public abstract function createCDATASection(string $data) : CDATASection;
	public abstract function createProcessingInstruction(string $target, string $data) : ProcessingInstruction;
	
	public abstract function importNode(Node $node, bool $deep = false) : Node;
	public abstract function adoptNode(Node $data) : Node;
	
	public abstract function createAttribute(string $localName) : Attr;
	public abstract function createAttributeNS(string $namespace, string $localName) : Attr;
}

abstract class DocumentFragment extends Node {
	use ParentNode;
	use NonElementParentNode;
}

abstract class DocumentType {
	use ChildNode;
	
	public $name;
	public $publicId;
	public $systemId;
}

abstract class Attr extends Node {
	public $namespaceURI;
	public $prefix;
	public $localName;
	
	public $name;
	public $value;
	public $ownerElement;
}

abstract class CharacterData extends Node {
	use ChildNode;
	use NonDocumentTypeChildNode;
	
	public $data;
	public $length;
	
	public abstract function substringData(int $offset, int $count) : string;
	public abstract function appendData(string $data) : void;
	public abstract function insertData(int $offset, string $data) : void;
	public abstract function deleteData(int $offset, int $count) : void;
	public abstract function replaceData(int $offset, int $count, string $data) : void;
}

abstract class Text extends CharacterData {
	use ChildNode;
	
	public $wholeText;
	
	public abstract function splitText(int $offset) : Text;
}

abstract class CDATASection extends Text {
	
}

abstract class ProcessingInstruction extends CharacterData {
	public $target;
}

abstract class Element extends Node {
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
	
	public abstract function hasAttributes() : bool;
	public abstract function getAttributeNames() : array;
	
	public abstract function getAttribute(string $qualifiedName) : string;
	public abstract function getAttributeNS(string $namespace, string $localName) : string;
	
	public abstract function setAttribute(string $qualifiedName, string $value) : void;
	public abstract function setAttributeNS(string $namespace, string $localName, string $value) : void;
	
	public abstract function removeAttribute(string $qualifiedName) : void;
	public abstract function removeAttributeNS(string $namespace, string $localName) : void;
	
	public abstract function toggleAttribute(string $qualifiedName, bool $force = NULL) : bool;
	public abstract function toggleAttributeNS(string $namespace, string $localName, bool $force = NULL) : bool;
	
	public abstract function hasAttribute(string $qualifiedName) : bool;
	public abstract function hasAttributeNS(string $namespace, string $localName) : bool;
	
	public abstract function getAttributeNode(string $qualifiedName) : Attr;
	public abstract function getAttributeNodeNS(string $namespace, string $localName) : Attr;
	
	public abstract function setAttributeNode(Attr $attr) : Attr;
	public abstract function setAttributeNodeNS(Attr $attr) : Attr;
	public abstract function removeAttributeNode(Attr $attr) : Attr;
	
	public abstract function closest($selectors) : Node;
	public abstract function matches($selectors) : bool;
	
	public abstract function insertAdjacentElement(string $where, Node $element) : Node; // historical
	public abstract function insertAdjacentText(string $where, string $data) : void; // historical
	public abstract function insertAdjacentHTML(string $where, string $html) : void; // historical
}

abstract class HTMLCollection implements \Iterator, \ArrayAccess, \Countable {
	public $length;
	public abstract function item(int $index) : Node;
	public abstract function namedItem(string $name) : Node;
}

abstract class NodeList implements \Iterator, \ArrayAccess, \Countable {
	public $length;
	public abstract function item(int $index) : Node;
}

abstract class DOMTokenList implements \Iterator, \ArrayAccess, \Countable {
	public $length;
	public $value;
	
	public abstract function item(int $index) : string;
	public abstract function contains(string $token) : bool;
	public abstract function add(string ...$tokens) : void;
	public abstract function remove(string ...$tokens) : void;
	public abstract function toggle(string $token, bool $force = NULL) : bool;
	public abstract function replace(string $token, string $newToken) : bool;
	public abstract function supports(string $token) : bool;
}

abstract class NamedNodeMap implements \Iterator, \ArrayAccess, \Countable {
	public $length;
	public $value;
	
	public abstract function item(int $index) : Attr;
	public abstract function getNamedItem(string $qualifiedName) : Attr;
	public abstract function getNamedItemNS(string $namespace, string $localName) : Attr;
	
	public abstract function setNamedItem(Attr $attr) : Attr;
	public abstract function setNamedItemNS(Attr $attr) : Attr;
	
	public abstract function removeNamedItem(string $qualifiedName) : Attr;
	public abstract function removeNamedItemNS(string $namespace, string $localName) : Attr;
}
