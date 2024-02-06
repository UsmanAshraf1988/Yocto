SUMMARY = "gps application"
DESCRIPTION = "gps application which uses gpsd recipe for libgps"
SECTION = "examples"
DEPENDS += "gpsd"
LICENSE = "CLOSED"

FILESEXTRAPATHS:prepend := "${THISDIR}/${PN}:"
SRC_URI = "file://gps_data_extractor.c "

do_compile () {
	${CC} ${CFLAGS} ${LDFLAGS} ${WORKDIR}/gps_data_extractor.c -o ${WORKDIR}/gps_data_extractor -l:libgps.so
}

do_install () {
	install -d ${D}${sbindir}
	install -m 0755 ${WORKDIR}/gps_data_extractor ${D}${sbindir}/

	install -d ${D}${bindir}
	install -m 0755 ${WORKDIR}/gps_data_extractor ${D}${bindir}/
}

RDEPENDS:${PN} = "gpsd"

FILES:${PN} += "${sbindir}/gps_data_extractor ${bindir}/gps_data_extractor"
FILES:${PN}-dbg += "${sbindir}/.debug/* ${bindir}/.debug/*"

