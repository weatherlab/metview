set(sources

    COUNTRYRSTRHBIAS.ddl
    aeolus.h
    allsky.h
    auxiliary.h
    body.h
    cloud_sink.h
    cma.h
    collocated_imager_information.h
    conv.h
    ensemble.h
    errstat.h
    forecast_diagnostic.h
    gbrad.h
    gnssro.h
    hdr.h
    idx.h
    limb.h
    mdi.h
    modsurf.h
    obstype.h
    ppcode.h
    radar.h
    radar_station.h
    radiance.h
    raingg.h
    resat.h
    sat.h
    satob.h
    scatt.h
    sensor.h
    smos.h
    ssmi1d.h
    surfbody_feedback.h
    type_definitions.h
    update.h
    varno.h
    vertco_type.h
)

set(views countryrstrhbody.sql countryrstrhhdr.sql)

odb_add_schema(TARGET COUNTRYRSTRHBIAS SOURCES ${sources} VIEWS ${views} CONDITION ODB_HAVE_COUNTRYRSTRHBIAS TYPE ${ODB_LIBS_TYPE})
