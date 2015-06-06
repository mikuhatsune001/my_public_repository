-----BEGIN PGP SIGNED MESSAGE-----
Hash: SHA512

Format: 1.0
Source: eglibc
Binary: libc-bin, libc-dev-bin, glibc-doc, eglibc-source, locales, locales-all, nscd, libc6, libc6-dev, libc6-dbg, libc6-prof, libc6-pic, libc6-udeb, libc6.1, libc6.1-dev, libc6.1-dbg, libc6.1-prof, libc6.1-pic, libc6.1-udeb, libc0.3, libc0.3-dev, libc0.3-dbg, libc0.3-prof, libc0.3-pic, libc0.3-udeb, libc0.1, libc0.1-dev, libc0.1-dbg, libc0.1-prof, libc0.1-pic, libc0.1-udeb, libc6-i386, libc6-dev-i386, libc6-sparc64, libc6-dev-sparc64, libc6-s390x, libc6-dev-s390x, libc6-amd64, libc6-dev-amd64, libc6-powerpc, libc6-dev-powerpc, libc6-ppc64, libc6-dev-ppc64, libc6-mipsn32, libc6-dev-mipsn32, libc6-mips64, libc6-dev-mips64, libc0.1-i386, libc0.1-dev-i386, libc6-sparcv9b, libc6-sparcv9v, libc6-sparcv9v2, libc6-sparc64b, libc6-sparc64v, libc6-sparc64v2, libc6-i686, libc6-xen, libc0.1-i686, libc6.1-alphaev67, libnss-dns-udeb, libnss-files-udeb
Architecture: any
Version: 2.11.1-0ubuntu7.13
Maintainer: Ubuntu Developers <ubuntu-devel-discuss@lists.ubuntu.com>
Uploaders: GOTO Masanori <gotom@debian.org>, Philip Blundell <pb@nexus.co.uk>, Jeff Bailey <jbailey@raspberryginger.com>, Daniel Jacobowitz <dan@debian.org>, Clint Adams <schizo@debian.org>, Aurelien Jarno <aurel32@debian.org>, Pierre Habouzit <madcoder@debian.org>
Homepage: http://www.eglibc.org
Standards-Version: 3.8.4
Vcs-Bzr: https://code.launchpad.net/~ubuntu-core-dev/eglibc/eglibc-2.11-pkg
Build-Depends: gettext, make (>= 3.80), dpkg-dev (>= 1.15.3.1), bzip2, lzma, xz-utils, file, quilt, texinfo (>= 4.0), texi2html, autoconf, sed (>= 4.0.5-4), gawk, debhelper (>= 5.0), tar (>= 1.22), linux-libc-dev [!hurd-i386 !kfreebsd-i386 !kfreebsd-amd64], mig (>= 1.3-2) [hurd-i386], hurd-dev (>= 20080607-3) [hurd-i386], gnumach-dev [hurd-i386], libpthread-stubs0-dev [hurd-i386], kfreebsd-kernel-headers [kfreebsd-i386 kfreebsd-amd64], binutils (>= 2.20-1), g++-4.4 (>= 4.4.3-4), g++-4.4-multilib [amd64 i386 kfreebsd-amd64 mips mipsel powerpc ppc64 s390 sparc]
Build-Depends-Indep: perl, po-debconf (>= 1.0)
Checksums-Sha1: 
 820de79d76c8b9194404029f4c8379811c6cdec7 23460095 eglibc_2.11.1.orig.tar.gz
 54adbd7fe5c02a308c9dc5c994541d0ddc1cd1e4 923724 eglibc_2.11.1-0ubuntu7.13.diff.gz
Checksums-Sha256: 
 7e349d22bcea45c33f9e59b8acf49f58166390f81ceacb3618f724c2d756e9fa 23460095 eglibc_2.11.1.orig.tar.gz
 d388faadb61473e220c949c0c482a393ed9339db8d5f336876acb47b8fe2f16e 923724 eglibc_2.11.1-0ubuntu7.13.diff.gz
Files: 
 26ec82ef1bd2644d1c2c872d8a6213e7 23460095 eglibc_2.11.1.orig.tar.gz
 3889c29a3312ee8bc4b3c1261ba86a6b 923724 eglibc_2.11.1-0ubuntu7.13.diff.gz
Debian-Vcs-Browser: http://svn.debian.org/wsvn/pkg-glibc/glibc-package/
Debian-Vcs-Svn: svn://svn.debian.org/pkg-glibc/glibc-package/
Original-Maintainer: GNU Libc Maintainers <debian-glibc@lists.debian.org>

-----BEGIN PGP SIGNATURE-----
Version: GnuPG v1.4.14 (GNU/Linux)

iQIcBAEBCgAGBQJSS3DoAAoJEGVp2FWnRL6TftwP+wcBezm5wczzcflw9MY1xtLp
aYRh1UYqW99nkqdSO+lOIez63KHlxGlQyo8MbeUFC4EFKcUzXvJlYg3agPRBAzDb
jtoN4vhOU7S4dPkVVF4JOImmTXE7v7+c6aOslmNrj6JpamIT4tVRa9iD1DS6VGSj
0rfZhHJiP+V5n466PoUXtYrjyzvVGSnQh1SrxLguZKMk8evwrYHXSfHO7o3aIXJu
PaSFwgdEsOASFS0mEwILbSw93oa8nIGpJJFzdlQaKPZetWMOCNmtlSFHPCT6Mq9P
1NIZa7DSLOBoBU+XFYnTwopjeURd4WAawIZqkcJkO9Ve0XdJINjIansY7uCW8DxX
+6PN5ZEz8gAlLoJFDfA73Q1JpK3tWEh52Q5gCJV/exvQQ74qhGLe2w3MY9YRqNOU
/Ydt++eeMmdLCIHIuPrSb19WaKnuI/wi2u8ShcwzM109qQuHYKelrSfyaZ88o/Z5
Aof499ueJdOOUIBW0rdgtxeFLIjUtDYYJA5o9S5XWtq6c5zT9MNL/S6GIlCaJ5Nv
UJ3EPfHl0hcQ4QLeUcl2cEmCZ1Y3fk7dYNtHwb1aCGF6eJZZVm2KG+Ebz9oMui01
YVe1BYObe6U15FZOIbml/Q+bD53rGae6evgXhTpjy/pXx2QAN2jVN5sAZe4B9FxL
X0CcDyqXmwfSU5HontGb
=sBNz
-----END PGP SIGNATURE-----
