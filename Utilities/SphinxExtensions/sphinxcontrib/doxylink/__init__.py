from .doxylink import __version__

def setup(app):
    from .doxylink import setup_doxylink_roles
    app.add_config_value('doxylink', {}, 'env')
    app.connect('builder-inited', setup_doxylink_roles)
