<?php
namespace HTML5;

abstract class DOM {
	public abstract function __construct(array $options = []);
	
	public abstract function parse(string $html, array $options = []) : DOM\Document;
	public abstract function parseChunkStart(array $options = []) : DOM\ChunksParser;
	
	public abstract function parseAsync(string $html, bool $loop = false, bool $callback = false, array $options = []) : DOM\AsyncResult;
	public abstract function parseAsyncChunkStart(bool $loop = false, bool $callback = false, array $options = []) : DOM\ChunksParserAsync;
}

namespace HTML5\DOM;

trait NonElementParentNode {
	/** @return Node|null */
	public abstract function getElementById(string $elementId);
}

trait ParentNode {
	public $children; // HTMLCollection
	public $firstElementChild;
	public $lastElementChild;
	public $childElementCount;
	
	public abstract function getElementsByTagName(string $qualifiedName) : HTMLCollection;
	public abstract function getElementsByTagNameNS(string $namespace, string $localName) : HTMLCollection;
	public abstract function getElementsByClassName(string $classNames) : HTMLCollection;
	
	/** @param Node|string ...$nodes */
	public abstract function prepend(...$nodes) : void;
	
	/** @param Node|string ...$nodes */
	public abstract function append(...$nodes) : void;
	
	/** @return Node|null */
	public abstract function querySelector(string $selectors) : Node;
	
	public abstract function querySelectorAll(string $selectors) : NodeList;
}

trait ChildNode {
	/** @param Node|string ...$nodes */
	public abstract function before(...$nodes) : void;
	
	/** @param Node|string ...$nodes */
	public abstract function after(...$nodes) : void;
	
	/** @param Node|string ...$nodes */
	public abstract function replaceWith(...$nodes) : void;
	
	public abstract function remove() : void;
}

trait NonDocumentTypeChildNode {
	public $previousElementSibling;
	public $nextElementSibling;
}

abstract class AsyncResult {
	public $done;
	
	private function __construct() { }
	public abstract function fd() : int;
	public abstract function wait() : Document;
}

abstract class ChunksParser {
	public $document;
	
	private function __construct() { }
	public abstract function parseChunk(string $html) : ChunksParser;
	public abstract function parseChunkEnd() : Document;
}

abstract class ChunksParserAsync {
	private function __construct() { }
	public abstract function parseChunk(string $html) : ChunksParserAsync;
	public abstract function parseChunkEnd() : AsyncResult;
}

abstract class DOMException extends \Exception {
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

abstract class EventTarget {
	private function __construct() { }
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
	
	public abstract function getRootNode(array $options = []) : Node;
	public abstract function hasChildNodes() : bool;
	public abstract function normalize() : void;
	public abstract function cloneNode(bool $deep = false) : Node;
	
	/** @param Node|null ...$otherNode */
	public abstract function isEqualNode(Node $otherNode) : bool;
	
	/** @param Node|null ...$otherNode */
	public abstract function isSameNode(Node $otherNode) : bool;
	
	public abstract function compareDocumentPosition(Node $other) : int;
	
	/** @param Node|null ...$other */
	public abstract function contains(Node $other) : bool;
	
	/** @param Node|null ...$child */
	public abstract function insertBefore(Node $node, Node $child) : Node;
	
	public abstract function appendChild(Node $child) : Node;
	
	public abstract function replaceChild(Node $node, Node $child) : Node;
	
	public abstract function removeChild(Node $child) : Node;
}

abstract class Document extends Node {
	use ParentNode;
	use NonElementParentNode;
	
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
	
	public abstract function createElement(string $localName) : Element;
	
	public abstract function createElementNS(string $namespace, string $qualifiedName) : Element;
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
	
	/** @return string|null */
	public abstract function getAttribute(string $qualifiedName) : string;
	
	/** @return string|null */
	public abstract function getAttributeNS(string $namespace, string $localName) : string;
	
	public abstract function setAttribute(string $qualifiedName, string $value) : void;
	public abstract function setAttributeNS(string $namespace, string $localName, string $value) : void;
	
	public abstract function removeAttribute(string $qualifiedName) : void;
	public abstract function removeAttributeNS(string $namespace, string $localName) : void;
	
	public abstract function toggleAttribute(string $qualifiedName, bool $force = NULL) : bool;
	public abstract function toggleAttributeNS(string $namespace, string $localName, bool $force = NULL) : bool;
	
	public abstract function hasAttribute(string $qualifiedName) : bool;
	public abstract function hasAttributeNS(string $namespace, string $localName) : bool;
	
	/** @return Attr|null */
	public abstract function getAttributeNode(string $qualifiedName) : Attr;
	
	/** @return Attr|null */
	public abstract function getAttributeNodeNS(string $namespace, string $localName) : Attr;
	
	/** @return Attr|null */
	public abstract function setAttributeNode(Attr $attr) : Attr;
	
	/** @return Attr|null */
	public abstract function setAttributeNodeNS(Attr $attr) : Attr;
	
	public abstract function removeAttributeNode(Attr $attr) : Attr;
	
	/** @return Node|null */
	public abstract function closest($selectors) : Node;
	
	public abstract function matches($selectors) : bool;
	
	/** @return Node|null */
	public abstract function insertAdjacentElement(string $where, Node $element) : Node; // historical
	
	public abstract function insertAdjacentText(string $where, string $data) : void; // historical
	
	public abstract function insertAdjacentHTML(string $where, string $html) : void; // historical
}

abstract class HTMLCollection implements \Iterator, \ArrayAccess, \Countable {
	public $length;
	
	/** @return Node|null */
	public abstract function item(int $index) : Node;
	
	/** @return Node|null */
	public abstract function namedItem(string $name) : Node;
}

abstract class NodeList implements \Iterator, \ArrayAccess, \Countable {
	public $length;
	
	/** @return Node|null */
	public abstract function item(int $index) : Node;
}

abstract class DOMTokenList implements \Iterator, \ArrayAccess, \Countable {
	public $length;
	public $value;
	
	/** @return string|null */
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
	
	/** @return Attr|null */
	public abstract function item(int $index) : Attr;
	
	/** @return Attr|null */
	public abstract function getNamedItem(string $qualifiedName) : Attr;
	
	/** @return Attr|null */
	public abstract function getNamedItemNS(string $namespace, string $localName) : Attr;
	
	/** @return Attr|null */
	public abstract function setNamedItem(Attr $attr) : Attr;
	
	/** @return Attr|null */
	public abstract function setNamedItemNS(Attr $attr) : Attr;
	
	public abstract function removeNamedItem(string $qualifiedName) : Attr;
	
	public abstract function removeNamedItemNS(string $namespace, string $localName) : Attr;
}
