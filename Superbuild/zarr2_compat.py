# itkwidgets (<=1.0a55) registers imjoy codecs against zarr.storage.BaseStore,
# which zarr 3 removed; alias it to the zarr 3 Store ABC.
try:
    import zarr.storage

    if not hasattr(zarr.storage, "BaseStore"):
        from zarr.abc.store import Store

        zarr.storage.BaseStore = Store
except ImportError:
    pass
