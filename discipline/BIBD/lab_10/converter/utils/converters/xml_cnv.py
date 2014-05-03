from datetime import datetime
import xml.etree.ElementTree as ET

def from_xml(table, xml_path):
    """ Import table data from xml file """
    XML = ET.ElementTree(file=xml_path)
    XMLTable = XML.getroot()

    if len(XMLTable) == 0:
        return

    headers = []
    types = []

    # fill headers and types information
    for field in XMLTable[0]:
        headers.append(field.tag)
        types.append(field.attrib["type"])

    table.headers = tuple(headers)
    table.types = tuple(types)

    table.check_types()

    # setup suitable converters list
    cnvs = []
    for idx, field in enumerate(XMLTable[0]):
        cnv_f = cnv_from[table.types[idx]]["f"]
        cnv_args = cnv_from[table.types[idx]]["args"]
        cnv_kwargs = cnv_from[table.types[idx]]["kwargs"]
        cnvs.append({
            "f": cnv_f,
            "args": cnv_args,
            "kwargs": cnv_kwargs
        })

    # fill table with data
    for XMLRow in XMLTable:
        row = []
        for idx, field in enumerate(XMLRow):
            imported = cnvs[idx]["f"](
                field.text,
                *cnvs[idx]["args"],
                **cnvs[idx]["kwargs"]
            )
            row.append(imported)
        table.data.append(tuple(row))


def to_xml(table, xml_path):
    """ Export table data to xml file """
    # setup suitable converters list
    cnvs = []
    for t in table.types:
        cnv_f = cnv_to[t]["f"]
        cnv_args = cnv_to[t]["args"]
        cnv_kwargs = cnv_to[t]["kwargs"]
        cnvs.append({
            "f": cnv_f,
            "args": cnv_args,
            "kwargs": cnv_kwargs
        })
    
    # fill xml with data
    XMLTable = ET.Element("table")
    for row in table.data:
        XMLRow = ET.SubElement(XMLTable, 'row')
        for idx, header in enumerate(table.headers):
            XMLField = ET.SubElement(XMLRow, header)
            XMLField.set("type", table.types[idx])
            XMLField.text = cnvs[idx]["f"](
                row[idx],
                *cnvs[idx]["args"],
                **cnvs[idx]["kwargs"]
            )
    XML = ET.ElementTree(XMLTable)
    XML.write(xml_path)
            

def bool_from_xml(field):
    """ Converts bool xml value to python bool """
    if field == "True":
        return True
    else:
        return False

def date_from_xml(field, date_format):
    """ Converts date xml value to python bool """
    date = datetime.strptime(field, date_format).date()
    return date

DEFAULT_ARGS = []
DEFAULT_KWARGS = {}

cnv_to = {
    "str": {
        "f": str,
        "args": DEFAULT_ARGS,
        "kwargs": DEFAULT_KWARGS
    },
    "unicode": {
        "f": unicode,
        "args": DEFAULT_ARGS,
        "kwargs": DEFAULT_KWARGS
    },
    "int": {"f": str,
            "args": DEFAULT_ARGS,
            "kwargs": DEFAULT_KWARGS
    },
    "float": {"f": str,
              "args": DEFAULT_ARGS,
              "kwargs": DEFAULT_KWARGS
    },
    "bool": {
        "f": str,
        "args": DEFAULT_ARGS,
        "kwargs": DEFAULT_KWARGS
    },
    "date": {
        "f": datetime.strftime,
        "args": ["%Y-%m-%d"],
        "kwargs": DEFAULT_KWARGS
    },
    "datetime": {
        "f": datetime.strftime,
        "args": ["%Y-%m-%d %H:%M:%S"],
        "kwargs": DEFAULT_KWARGS
    },
    
}

cnv_from = {
    "str": {
        "f": str,
        "args": DEFAULT_ARGS,
        "kwargs": DEFAULT_KWARGS
    },
    "unicode": {
        "f": unicode,
        "args": DEFAULT_ARGS,
        "kwargs": DEFAULT_KWARGS
    },
    "int": {
        "f": int,
        "args": DEFAULT_ARGS,
        "kwargs": DEFAULT_KWARGS
    },
    "float": {
        "f": float,
        "args": DEFAULT_ARGS,
        "kwargs": DEFAULT_KWARGS
    },
    "bool": {
        "f": bool_from_xml,
        "args": DEFAULT_ARGS,
        "kwargs": DEFAULT_KWARGS
    },
    "date": {
        "f": date_from_xml,
        "args": ["%Y-%m-%d"],
        "kwargs": DEFAULT_KWARGS
    },
    "datetime": {
        "f": datetime.strptime,
        "args": ["%Y-%m-%d %H:%M:%S"],
        "kwargs": DEFAULT_KWARGS
    },
}


