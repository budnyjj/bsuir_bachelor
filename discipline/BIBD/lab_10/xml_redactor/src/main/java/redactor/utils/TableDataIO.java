package redactor.utils;

import java.io.File;
import java.io.FileInputStream;
import java.io.FileOutputStream;
import java.io.IOException;

import java.util.List;
import java.util.ArrayList;

import com.thoughtworks.xstream.XStream;
import com.thoughtworks.xstream.XStreamException;
import com.thoughtworks.xstream.io.xml.DomDriver;

import redactor.model.TableData;
import redactor.utils.TableConverter;

public class TableDataIO {
    private static XStream xStream =
        new XStream(new DomDriver());;
    
    public TableDataIO() {
        xStream.registerConverter(new TableConverter());
        xStream.alias("table", TableData.class);
    }

    public static void toXML(TableData tableData, File XMLFile) {
        System.out.println(XMLFile.toString());
        try (FileOutputStream oStream = new FileOutputStream(XMLFile)) {
                if (!XMLFile.exists()) {
                    XMLFile.createNewFile();
                }
                xStream.toXML(tableData, oStream);
                oStream.flush();
                oStream.close();
        } catch (IOException e) {
            e.printStackTrace();
        }
    }

    public static TableData fromXML(File XMLFile) {
        TableData tableData = null;
        System.out.println(XMLFile.toString());
        try (FileInputStream iStream = new FileInputStream(XMLFile)) {                
                tableData = (TableData) xStream.fromXML(iStream);
            }
        catch (Exception e) {
            return null;
        }
        return tableData;
    }
}
