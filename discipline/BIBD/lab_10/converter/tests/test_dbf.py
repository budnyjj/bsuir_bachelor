import env

import unittest

from dbf import DbfError
import datetime as dt
import utils.converters.dbf_cnv as dbf
import utils.table as tbl

sample_headers = ("name", "age", "temp", "birth", "married")
sample_types = ("unicode", "int", "float", "date", "bool")
sample_data = [(u"John Doe", 31, 36.6, dt.date(1979, 9, 13), True),
               (u"Ethan Furman", 102, 3.14159, dt.date(1909, 4, 1), False),
               (u"Jane Smith", 57, 0.000, dt.date(1954, 7, 2), True),
               (u"John Adams", 44, 2.0, dt.date(1967, 1, 9), False)]


class DBFConverterTest(unittest.TestCase):
    def test_basic_case(self):
        init_table = tbl.DataTable(sample_data, sample_headers, sample_types)
        new_table = tbl.DataTable()

        dbf.to_dbf(init_table, "files/basic_data.dbf")
        dbf.from_dbf(new_table, "files/basic_data.dbf")
        self.__assertEqualTables(init_table, new_table)

    def test_single_case(self):
        init_table = tbl.DataTable(
            data=[(u"abc",),],
            headers=("field_1",),
            types=("unicode", ))
        new_table = tbl.DataTable()

        dbf.to_dbf(init_table, "files/single_data.dbf")
        dbf.from_dbf(new_table, "files/single_data.dbf")
        self.__assertEqualTables(init_table, new_table)

    def test_empty_case(self):
        init_table = tbl.DataTable()
        new_table = tbl.DataTable()

        dbf.to_dbf(init_table, "files/empty_data.dbf")
        self.assertRaises( # db not exists
            DbfError,
            dbf.from_dbf, new_table, "files/empty_data.dbf"
        )
        

    def test_incorrect_type_case(self):
        init_table = tbl.DataTable(
            data=[("abc",),],
            headers=("field_1",),
            types=("int", ))
        new_table = tbl.DataTable()

        self.assertRaises(
            DbfError,
            dbf.to_dbf, init_table, "files/single_data.dbf"
        )

    def test_from_not_existing_case(self):
        new_table = tbl.DataTable()
        self.assertRaises(
            DbfError,
            dbf.from_dbf, new_table, "files/not_existing.dbf"
        )

    def test_from_empty_path_case(self):
        new_table = tbl.DataTable()
        self.assertRaises(
            DbfError,
            dbf.from_dbf, new_table, ""
        )        


    def __assertEqualTables(self, table_a, table_b):
        self.assertEqual(table_a.headers, table_b.headers)
        self.assertEqual(table_a.types, table_b.types)
        self.assertEqual(table_a.data, table_b.data)


if __name__ == '__main__':
    unittest.main()
