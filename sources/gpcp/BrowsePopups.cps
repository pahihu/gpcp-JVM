ޭ��H$  BrowsePopupsI$  RTSK    C$ stylePrefixs�<style>
<!-- BEGIN Inline CSS -->
/* Popup container */
.popup {
    position: relative;
    display: inline-block;
    cursor: pointer;
}

/* The actual popup (appears on top) */
.popup .popuptext {
    visibility: hidden;
    width: 430px;
    background-color: white;
    color: black;
    text-align: left;
    border-radius: 6px;
    border-style: solid;
    border-color: black;
    padding: 8px 8px 8px 8px;
    position: absolute;
    z-index: 1;
    margin-top: 30px;
}

/* Toggle this class when clicking on the popup container (hide and show the popup) */
.popup .show {
    visibility: visible;
    opacity: 1;
}

</style>
<!-- END Inline CSS -->C$ 
ecmaScriptsb<!-- BEGIN JavaScript -->
<script>
function toggle(node) {
    node.classList.toggle("show"); 
  }

function cls(node) {
    var prnt = node.parentNode;
    var next = prnt.previousSibling;
    var text = next.lastChild;
    text.innerHTML = 
        "The <b>class</b> property asserts that this type will be<br>" +
        "implemented as a reference class in the underlying framework.";
    text.classList.toggle("show");
  }

function newOk(node) {
    var popuptext = node.parentNode.previousSibling.lastChild;
    popuptext.innerHTML = 
        "The <b>has noArg-ctor</b> property asserts that this reference<br>" +
        "class has a no-arg constructor, and thus objects of this<br>" +
        "type can be allocated with NEW(). Component Pascal types<br>" +
        "derived from this type can also be allocated using NEW().";
    popuptext.classList.toggle("show"); 
  }

function noNew(node) { 
    var prnt = node.parentNode; 
    var next = prnt.previousSibling; 
    var text = next.lastChild; 
    text.innerHTML =  
        "The <b>no noArg-ctor</b> property asserts that this reference<br>" +
        "class does not have a noArg constructor. Objects of this<br>" +
        "type cannot be allocated using NEW(), and Component<br>" +
        "Pascal types  derived from this type also cannot be<br>" +
        "allocated using NEW().";
    text.classList.toggle("show");
  }

function noCpy(node) {
    var popuptext = node.parentNode.previousSibling.lastChild;
    popuptext.innerHTML = 
        "The <b>no value-assign</b> property asserts that this reference<br>" + 
        "class does not have a value copy method. Therefore, it<br>" +
        "is not possible to perform value assignments using<br>" +
        "statements like <i>dst^</i> := <i>src^</i>";
    popuptext.classList.toggle("show");
  }

function valueclass(node) { 
        var popuptext = node.parentNode.previousSibling.lastChild; 
    popuptext.innerHTML =  
        "The <b>valueclass</b> property asserts that this RECORD type is<br>" + 
        "implemented as a value class in the CLR. It follows that<br>" +  
        "value assignments can be made of these types. They can<br>" + 
        "also be passed by value. Even pointers to records of<br>" + 
        "such types may be dereferenced and copied using syntax<br>" + 
        "such as  <i>dst^</i> := <i>src^</i>"; 
    popuptext.classList.toggle("show"); 
  } 

function argCtor(node) { 
    var popuptext = node.parentNode.previousSibling.lastChild; 
    popuptext.innerHTML =  
        "The <b>has arg-ctor</b> property asserts that this reference<br>" +  
        "class has one or more constructors that take arguments.<br>" + 
        "These constructors can be called from Component Pascal<br>" + 
        "by calling an <i>init</i>(...) method from the static list<br>" + 
        "here. Component Pascal types derived from this type<br>" + 
        "can define constructors with arguments which call the<br>" + 
        "super-type constructor.<br>" + 
        "See <i>'Interfacing to constructors'</i> in the Release Notes."; 
    popuptext.classList.toggle("show"); 
  } 

</script>
<!-- END JavaScript --> 
&!K��ٶ