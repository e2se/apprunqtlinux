# apprunqtlinux

Tiny AppRun launcher for AppImage and the runtime `AppImage/type2-runtime`.

I used this to fix `argv[0]` when using `conda-forge::qt6-main` recent builds. 

It relies on `/proc/self/exe`, `getauxval(AT_EXECFN)`, `getenv("APPDIR")` for path resolving and fixes `argv[0]` with the mount absolute path.

This to meet the Qt6 logic to locate `qt.conf`.

## Usage
```
./[FILE].Appimage --appimage-extract

mv squashfs-root/AppRun squashfs-root/AppRun.wrapped

cmake -B build -DCMAKE_BUILD_TYPE=Release
cmake --build build --config Release

cp build/AppRun squashfs-root/AppRun
chmod +x squashfs-root/AppRun
```

## License

Source code licensed under the terms of the [MIT License](https://github.com/e2se/apprunqtlinux/blob/main/LICENSE-MIT).

It is also licensed under the terms of the [GNU GPLv3](https://github.com/e2se/apprunqtlinux/blob/main/LICENSE-GPL-3.0-or-later).

