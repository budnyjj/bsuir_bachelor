#!/usr/bin/python2

from dbf import DbfError
from gi.repository import Gtk

import utils.converters.xml_cnv as xml
import utils.converters.dbf_cnv as dbf 
import utils.table as tbl

def get_builder():
    builder = None

    def tmp(builder):
        if builder == None:
            builder = Gtk.Builder()
        return builder            
    return tmp(builder)

class TypeFilters:
    def add_xml_filter(self, dialog):
        filter_xml = Gtk.FileFilter()
        filter_xml.set_name("XML files")
        filter_xml.add_pattern("*.xml")
        dialog.add_filter(filter_xml)

    def add_dbf_filter(self, dialog):
        filter_dbf = Gtk.FileFilter()
        filter_dbf.set_name("DBF files")
        filter_dbf.add_pattern("*.dbf")
        filter_dbf.add_pattern("*.DBF")
        dialog.add_filter(filter_dbf)

    def add_any_filter(self, dialog):
        filter_any = Gtk.FileFilter()
        filter_any.set_name("Any files")
        filter_any.add_pattern("*")
        dialog.add_filter(filter_any)
        
class MainWindow:
    builder = get_builder()

    def __init__(self):
        self.glade_file = "view/main_window.glade"

        self.builder.add_from_file(self.glade_file)

        # connect handler with MainWindow object
        self.builder.connect_signals(Handler(self))

        self.window = self.builder.get_object("main_window")
        self.window.connect("delete-event", Gtk.main_quit)

        self.xml_file_entry = self.builder.get_object("xml_file-entry")
        self.dbf_file_entry = self.builder.get_object("dbf_file-entry")

        self.status_bar = self.builder.get_object("status_bar")
        self.status_bar.push(0, "Ready!")

        self.window.show_all()

class Handler:
    builder = get_builder()
    filters = TypeFilters()

    def __init__(self, view):
        self.view = view

    def on_quit_button_clicked(self, *args):
        Gtk.main_quit(*args)

    def on_select_xml_file_button_clicked(self, button, data=None):
        dialog = Gtk.FileChooserDialog(
            title="Select XML file dialog", 
            action=Gtk.FileChooserAction.OPEN,
            buttons=(
                Gtk.STOCK_CANCEL,
                Gtk.ResponseType.CANCEL,
                Gtk.STOCK_OPEN,
                Gtk.ResponseType.OK
            )
        )
        
        self.filters.add_xml_filter(dialog)
        self.filters.add_any_filter(dialog)

        response = dialog.run()
        if response == Gtk.ResponseType.OK:
            self.view.xml_file_entry.set_text(dialog.get_filename())

        dialog.destroy()

    def on_select_dbf_file_button_clicked(self, button, data=None):
        dialog = Gtk.FileChooserDialog(
            title="Select DBF file dialog", 
            action=Gtk.FileChooserAction.OPEN,
            buttons=(
                Gtk.STOCK_CANCEL,
                Gtk.ResponseType.CANCEL,
                Gtk.STOCK_OPEN,
                Gtk.ResponseType.OK
            )
        )
        
        self.filters.add_dbf_filter(dialog)
        self.filters.add_any_filter(dialog)

        response = dialog.run()
        if response == Gtk.ResponseType.OK:
            self.view.dbf_file_entry.set_text(dialog.get_filename())

        dialog.destroy()

    def on_convert_to_xml_button_clicked(self, button, data=None):
        xml_path = self.view.xml_file_entry.get_text()
        if xml_path == "":
            self.view.status_bar.push(0, "Please, specify XML path!")
            return
        elif (not xml_path.endswith(".xml")):
              xml_path += ".xml"

        dbf_path = self.view.dbf_file_entry.get_text()
        if dbf_path == "":
            self.view.status_bar.push(0, "Please, specify DBF path!")
            return

        self.view.status_bar.push(0, "Converting DBF to XML...")

        table = tbl.DataTable()

        try:
            dbf.from_dbf(table, dbf_path)
        except DbfError as e:
            self.view.status_bar.push(0, "DBF: {e}".format(e=e))
            return
        else:
            self.view.status_bar.push(0, "Succeed!")

        try:
            xml.to_xml(table, xml_path)
        except IOError as e:
            self.view.status_bar.push(0, "XML: {e}".format(e=e))
            return
        else:
            self.view.status_bar.push(0, "Succeed!")
        
        self.view.status_bar.push(0, "Ready!")

    def on_convert_to_dbf_button_clicked(self, button, data=None):
        xml_path = self.view.xml_file_entry.get_text()
        if xml_path == "":
            self.view.status_bar.push(0, "Please, specify XML path!")
            return
        elif (not xml_path.endswith(".xml")):
              xml_path += ".xml"

        dbf_path = self.view.dbf_file_entry.get_text()
        if dbf_path == "":
            self.view.status_bar.push(0, "Please, specify DBF path!")
            return

        self.view.status_bar.push(0, "Converting XML to DBF...")

        table = tbl.DataTable()
        try:
            xml.from_xml(table, xml_path)
        except IOError as e:
            self.view.status_bar.push(0, "XML: {e}".format(e=e))
            return
        else:
            self.view.status_bar.push(0, "Succeed!")

        try:
            dbf.to_dbf(table, dbf_path)
        except DbfError as e:
            self.view.status_bar.push(0, "DBF: {e}".format(e=e))
            return
        else:
            self.view.status_bar.push(0, "Succeed!")
        
        self.view.status_bar.push(0, "Ready!")

if __name__ == "__main__":
    main_window = MainWindow()
    Gtk.main()
