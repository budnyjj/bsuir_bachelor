from datetime import datetime

class DataTable:
    """ Data container, which represents single table.
    Table data is stored in self.data by this way:
    [{"attr_name": "attr_value"}, {}, {}] """
    def __init__(self, data=None, headers=None, types=None):
        self.data = (data if data is not None else [])
        self.headers = (headers if headers is not None else ())
        self.types = (types if types is not None else ())

        # check types for correctness
        self.check_types()

    def __repr__(self):
        headers = "|"
        for idx, header in enumerate(self.headers):
            headers += " {h:>10} ({t:^5}) |".format(h=header, t=self.types[idx])
        headers += "\n"

        values = ""
        for row in self.data:
            value = "|"
            for val in row:
                value += " {v:>18} |".format(v=str(val))
            values += value + "\n"

        return headers + values

    def check_types(self):
        for tp in self.types:
            if tp not in supported_types:
                raise ValueError(
                    "Support for type {t} is not implemented yet!".format(t=tp))

supported_types = (
    "str",
    "unicode",
    "int",
    "float",
    "bool",
    "date",
    "datetime",
)
        


