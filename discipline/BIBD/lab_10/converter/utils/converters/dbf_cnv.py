from datetime import datetime
import dbf

def from_dbf(table, dbf_path):
    """ Import table data from dbf file """
    DBFTable = dbf.Table(dbf_path)
    DBFTable.open()

    table.headers = tuple(DBFTable.field_names)

    types = []
    for field in DBFTable[0]:
        types.append(field.__class__.__name__)

    table.types = tuple(types)
    table.check_types()

    for row in DBFTable:
        table_row = []
        for field in row:
            # strip string values
            if isinstance(field, (str, unicode)):
                table_row.append(field.strip())
            else:
                table_row.append(field)
        table.data.append(tuple(table_row))

def to_dbf(table, dbf_path):
    """ Export table data to dbf file """
    if len(table.headers) == 0:
        return

    # determine db schema
    DBFHeader = "; ".join("{h} {ct}".format(
        h=header, ct=cnv_to[table.types[idx]])
              for idx, header in enumerate(table.headers))

    DBFTable = dbf.Table(dbf_path, DBFHeader)
    with DBFTable:    
        for row in table.data:
            DBFTable.append(row)

# type conversions for dbf format
cnv_to = {
    "str": "C(254)",
    "unicode": "C(254)",
    "int": "N(17,0)",
    "float": "N(17,7)",
    "bool": "L",
    "date": "D",
    "datetime": "D",
}
