import env

import unittest

import datetime as dt
import utils.converters.xml_cnv as xml
import utils.table as tbl

sample_headers = ("name", "age", "temp", "birth", "married")
sample_types = ("unicode", "int", "float", "date", "bool")
sample_data = [(u"John Doe", 31, 36.6, dt.date(1979, 9, 13), True),
               (u"Ethan Furman", 102, 3.14159, dt.date(1909, 4, 1), False),
               (u"Jane Smith", 57, 0.000, dt.date(1954, 7, 2), True),
               (u"John Adams", 44, 2.0, dt.date(1967, 1, 9), False)]


class XMLConverterTest(unittest.TestCase):
    def test_basic_case(self):
        init_table = tbl.DataTable(sample_data, sample_headers, sample_types)
        new_table = tbl.DataTable()

        xml.to_xml(init_table, "files/basic_data.xml")
        xml.from_xml(new_table, "files/basic_data.xml")
        self.__assertEqualTables(init_table, new_table)

    def test_single_case(self):
        init_table = tbl.DataTable(
            data=[("abc",),],
            headers=("field_1",),
            types=("str", ))
        new_table = tbl.DataTable()

        xml.to_xml(init_table, "files/single_data.xml")
        xml.from_xml(new_table, "files/single_data.xml")
        self.__assertEqualTables(init_table, new_table)


    def test_empty_case(self):
        init_table = tbl.DataTable()
        new_table = tbl.DataTable()

        xml.to_xml(init_table, "files/empty_data.xml")
        xml.from_xml(new_table, "files/empty_data.xml")
        self.__assertEqualTables(init_table, new_table)

    def test_incorrect_type_case(self):
        init_table = tbl.DataTable(
            data=[("abc",),],
            headers=("field_1",),
            types=("int", ))
        new_table = tbl.DataTable()

        xml.to_xml(init_table, "files/single_data.xml")

        self.assertRaises(
            ValueError,
            xml.from_xml, new_table, "files/single_data.xml"
        )

    def test_from_not_existing_case(self):
        new_table = tbl.DataTable()
        self.assertRaises(
            IOError,
            xml.from_xml, new_table, "files/not_existing.xml"
        )

    def __assertEqualTables(self, table_a, table_b):
        self.assertEqual(table_a.headers, table_b.headers)
        self.assertEqual(table_a.types, table_b.types)
        self.assertEqual(table_a.data, table_b.data)


if __name__ == '__main__':
    unittest.main()
