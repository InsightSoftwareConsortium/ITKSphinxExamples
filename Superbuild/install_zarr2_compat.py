"""Install the zarr2 compatibility shim into this interpreter's site-packages."""

import pathlib
import shutil
import sysconfig

site_packages = pathlib.Path(sysconfig.get_paths()["purelib"])
shutil.copy(pathlib.Path(__file__).parent / "zarr2_compat.py", site_packages)
(site_packages / "zarr2_compat.pth").write_text("import zarr2_compat\n")
