// Everything lives in the itk namespace.
var itk = itk || {};

itk.webglCheck = function() {
  itk.HAS_WEBGL = true;
  var suggestion = document.createElement("p");

  if (!window.WebGLRenderingContext) {
    var getWebGLA = document.createElement("a");
    getWebGLA.setAttribute("href", "http://get.webgl.org");
    var getWebGLAText = document.createTextNode("A browser that supports the WebGl standard");
    getWebGLA.appendChild(getWebGLAText);
    suggestion.appendChild(getWebGLA);
    var suggestionText = document.createTextNode(" is required to view the interactive 3D visualizations.");
    suggestion.appendChild(suggestionText);

    itk.HAS_WEBGL = false;
    }
  else {
    var canvas = document.getElementById("testCanvas");
    var gl = canvas.getContext("webgl");
    if (!gl) {
      var preSuggestionText = document.createTextNode("WebGL could not be loaded. ");
      suggestion.appendChild(preSuggestionText);
      var getWebGLA = document.createElement("a");
      getWebGLA.setAttribute("href", "http://get.webgl.org/troubleshooting");
      var getWebGLAText = document.createTextNode("A different browser or video drivers ");
      getWebGLA.appendChild(getWebGLAText);
      suggestion.appendChild(getWebGLA);
      var suggestionText = document.createTextNode(" may be required to view the interactive 3D visualizations.");
      suggestion.appendChild(suggestionText);

      itk.HAS_WEBGL = false;
    }
  }

  if (!itk.HAS_WEBGL) {
    suggestion.setAttribute("class", "last");
    var warning = document.createElement("div");
    warning.setAttribute("id", "webglWarning");
    warning.setAttribute("class", "admonition note");
    var note = document.createElement("p");
    note.setAttribute("class", "first admonition-title");
    var noteText = document.createTextNode("Note");
    note.appendChild(noteText);
    warning.appendChild(note);
    var webglError = document.createElement("p");
    var webglErrorText = document.createTextNode("WebGL support was not detected.");
    webglError.appendChild(webglErrorText);
    warning.appendChild(webglError);
    warning.appendChild(suggestion);
    var body = $(".body")[0];
    if( body ) {
      body.insertBefore(warning, body.childNodes[0]);
    }
  }
}

$( document ).ready( itk.webglCheck );
