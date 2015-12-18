// Everything lives in the itk namespace.
var itk = itk || {};

itk.selectLanguage = function() {
  var language = document.getElementById( 'languageSelection' ).value;
  if( language == 'Python' )
    {
    $( "h3:contains('C++')" ).hide('fast');
    $( "h3:contains('C++') + div").hide('fast');
    $( "h3:contains('Python')" ).show('fast');
    $( "h3:contains('Python') + div" ).show('fast');
    itk.createCookie( 'programming_language', language, 365 );
    }
  else if( language == 'C++' )
    {
    $( "h3:contains('C++')" ).show('fast');
    $( "h3:contains('C++') + div").show('fast');
    $( "h3:contains('Python')" ).hide('fast');
    $( "h3:contains('Python') + div" ).hide('fast');
    itk.createCookie( 'programming_language', language, 365 );
    }
  else
    {
    $( "h3:contains('C++')" ).show('fast');
    $( "h3:contains('C++') + div").show('fast');
    $( "h3:contains('Python')" ).show('fast');
    $( "h3:contains('Python') + div" ).show('fast');
    itk.createCookie( 'programming_language', '', 365 );
    }
}

$(document).ready(function(){
  var code_elements = $( "h2:contains('Code')" );
  if( code_elements ) {
    code_elements.append(" \
    <select class=\"form-control\" id=\"languageSelection\" onchange=\"itk.selectLanguage()\"> \
      <option>All</option> \
      <option>C++</option> \
      <option>Python</option> \
    </select> " );
  }

  var language = itk.readCookie( 'programming_language' );
  if( language )
    {
    document.getElementById( 'languageSelection' ).value = language;
    itk.selectLanguage();
    }
});
