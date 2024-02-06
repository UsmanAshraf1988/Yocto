SUMMARY = "dumpinfo library"
DESCRIPTION = "dumpinfo library used for hello world application"
SECTION = "examples"
LICENSE = "CLOSED"

FILESEXTRAPATHS:prepend := "${THISDIR}/${PN}:"
SRC_URI = "file://dump_info.h file://dump_info.c "

do_compile () {
	${CC} ${CFLAGS} ${LDFLAGS} -shared -fPIC -Wl,-soname,libdumpinfo.so.${PV} ${WORKDIR}/dump_info.c -o ${WORKDIR}/libdumpinfo.so.${PV}
}

do_install () {
	install -d ${D}${includedir}
	install -m 0644 ${WORKDIR}/dump_info.h ${D}${includedir}/

	install -d ${D}${libdir}
	install -m 0755 ${WORKDIR}/libdumpinfo.so.${PV} ${D}${libdir}/
}


FILES:${PN}-dev += "${includedir}/dump_info.h"

