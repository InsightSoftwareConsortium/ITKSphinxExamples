var color_theme = readCookie( 'color_theme' );
if( color_theme == 'dark' )
  {
  window.location = "dark/index.html"
  }
else // defaults to light
  {
  window.location = "light/index.html"
  }
