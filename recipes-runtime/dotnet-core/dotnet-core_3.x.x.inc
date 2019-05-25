###################################################################################################
# Contains additional parameters for the recipe to download the release binaries from Microsoft
# pertaining to all 3.x.x versions.
# Copyright Richard Dunkley 2019
###################################################################################################
DESCRIPTION = "This does not build this version, it only pulls the binaries from Microsoft"
BUGTRACKER = "https://github.com/dotnet/core/issues"
SECTION = "runtime"

S = "${WORKDIR}/dotnet-${PV}"

require recipes-runtime/dotnet-core/dotnet-core_mit_3.x.x.inc

DEPENDS = "zlib"
RDEPENDS_${PN} = "dotnet-core-staticdev icu lttng-tools lttng-ust zlib curl libgssglue"

INSANE_SKIP_${PN} += "already-stripped libdir textrel"
INSANE_SKIP_${PN}-dbg += "libdir"

do_configure[noexec] = "1"
do_compile[noexec] = "1"

#PACKAGES =+ "${PN}-dbg ${PN}-staticdev ${PN}"

#FILES_${PN} += "${datadir}"
#FILES_${PN} += ""

FILES_${PN} += " \
	${datadir}/dotnet/dotnet \
	${datadir}/dotnet/*.txt \
	${datadir}/dotnet/host/fxr/${PV}-preview5-27626-15/*.so \
	${datadir}/dotnet/shared/Microsoft.NETCore.App/${PV}-preview5-27626-15/.version \
	${datadir}/dotnet/shared/Microsoft.NETCore.App/${PV}-preview5-27626-15/*.so \
	${datadir}/dotnet/shared/Microsoft.NETCore.App/${PV}-preview5-27626-15/*.dll \
	${datadir}/dotnet/shared/Microsoft.NETCore.App/${PV}-preview5-27626-15/*.json \
	${datadir}/dotnet/shared/Microsoft.NETCore.App/${PV}-preview5-27626-15/*.txt \
	"


FILES_${PN}-staticdev += " \
	${datadir}/dotnet/shared/Microsoft.NETCore.App/${PV}-preview5-27626-15/*.a \
	"

do_install_prepend () {
	install -d ${D}${bindir}
	install -d ${D}${datadir}/dotnet/
	install -m 0755 ${S}/dotnet ${D}${datadir}/dotnet/
	install -m 0644 ${S}/LICENSE.txt ${D}${datadir}/dotnet/
	install -m 0644 ${S}/ThirdPartyNotices.txt ${D}${datadir}/dotnet/

	install -d ${D}${datadir}/dotnet/host/fxr/${PV}-preview5-27626-15/
	install -m 0755 ${S}/host/fxr/${PV}-preview5-27626-15/libhostfxr.so ${D}${datadir}/dotnet/host/fxr/${PV}-preview5-27626-15/

	install -d ${D}${datadir}/dotnet/shared/Microsoft.NETCore.App/${PV}-preview5-27626-15/
	
	install -m 0644 ${S}/shared/Microsoft.NETCore.App/${PV}-preview5-27626-15/.version ${D}${datadir}/dotnet/shared/Microsoft.NETCore.App/${PV}-preview5-27626-15/.version
	for file in ${S}/shared/Microsoft.NETCore.App/${PV}-preview5-27626-15/*.so; do
		install -m 0755 "$file" ${D}${datadir}/dotnet/shared/Microsoft.NETCore.App/${PV}-preview5-27626-15/
	done
	for file in ${S}/shared/Microsoft.NETCore.App/${PV}-preview5-27626-15/{*.dll,*.json,*.txt,*.a}; do
		install -m 0644 "$file" ${D}${datadir}/dotnet/shared/Microsoft.NETCore.App/${PV}-preview5-27626-15/
	done
}

do_install_append() {
    cd ${D}${bindir}
    ln -s ../share/dotnet/dotnet ${D}${bindir}/dotnet
}
