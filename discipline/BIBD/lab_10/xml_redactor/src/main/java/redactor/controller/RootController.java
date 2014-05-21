package redactor.controller;

import java.io.File;

import javafx.fxml.FXML;

import javafx.scene.control.TableView;
import javafx.scene.control.TableRow;
import javafx.scene.control.TableColumn;
import javafx.scene.control.TableCell;
import javafx.scene.control.ContextMenu;
import javafx.scene.control.MenuItem;
import javafx.scene.control.SeparatorMenuItem;
import javafx.scene.control.SelectionMode;
import javafx.scene.text.Text;

import javafx.event.ActionEvent;
import javafx.event.EventHandler;

import javafx.stage.FileChooser;

import javafx.collections.FXCollections;
import javafx.collections.ObservableList;

import javafx.beans.binding.Bindings;
import javafx.beans.value.ObservableValue;
import javafx.beans.value.ObservableNumberValue;
import javafx.beans.property.SimpleStringProperty;

import javafx.util.Callback;

import redactor.Main;
import redactor.model.RowData;
import redactor.model.TableData;

import redactor.utils.EditingCell;
import redactor.utils.TableDataIO;

public class RootController {

    @FXML
    private TableView<RowData> tableView;

    private Main mainApp;

    private File XMLFile = null;
    private final FileChooser fileChooser = new FileChooser();
    private static TableDataIO tableDataIO = new TableDataIO();

    public RootController() { }

    public void setMainApp(Main mainApp) {
        this.mainApp = mainApp;
    }

    @FXML
    private void initialize() {
        tableView.setColumnResizePolicy(TableView.CONSTRAINED_RESIZE_POLICY);
        tableView.getSelectionModel().setSelectionMode(SelectionMode.SINGLE);

        // define context menu
        final ContextMenu menu = new ContextMenu();

        // delete all rows
        final MenuItem deleteAllRowsItem = new MenuItem("Clear all");
        deleteAllRowsItem.setOnAction(new EventHandler<ActionEvent>() {
                @Override
                    public void handle(ActionEvent event) {
                    TableData tableData = mainApp.getTableData();

                    tableData.getRows().clear();
                    RowData emptyRow = new RowData(tableData.getAttributes().size());
                    tableData.getRows().add(emptyRow);
                    loadTable();
                }
            });

        menu.getItems().add(deleteAllRowsItem);
        tableView.setContextMenu(menu);
    }

    @FXML
    private void onOpen(ActionEvent event) {
        File file = fileChooser.showOpenDialog(mainApp.getPrimaryStage());
        if (file != null && file.exists()) {
            TableData tableData = (TableData) tableDataIO.fromXML(file);
            if (tableData != null) {
                XMLFile = file;
                mainApp.setTableData(tableData);
                loadTable();             
            }
        }
    }

    @FXML
    private void onSave(ActionEvent event) {
        if (XMLFile != null) {
            tableDataIO.toXML(mainApp.getTableData(), XMLFile);
        } else {
            File file = fileChooser.showSaveDialog(mainApp.getPrimaryStage());
            if (file != null) {
                XMLFile = file;
                tableDataIO.toXML(mainApp.getTableData(), XMLFile);
            } 
        }
    }

    @FXML
    private void onSaveAs(ActionEvent event) {
        File file = fileChooser.showSaveDialog(mainApp.getPrimaryStage());
        if (file != null) {
            XMLFile = file;
            tableDataIO.toXML(mainApp.getTableData(), XMLFile);
        }
    }

    @FXML
    private void onExit(ActionEvent event) {
        mainApp.getPrimaryStage().close();
    }

    @FXML
    private void onLoadSampleData(ActionEvent event) {
        TableData tableData = new TableData();        

        for (int j = 0; j < 7; j++) {
            tableData.getAttributes().add("Attr" + j);
            tableData.getTypes().add("unicode");
        }

        for (int i = 0; i < 10; i++) {
            RowData tmpRow = new RowData();
            for (int j = 0; j < 7; j++) {
                tmpRow.getValues().add("Value #" + i + ": " + j);
            }
            tableData.getRows().add(tmpRow);
        }

        mainApp.setTableData(tableData);
        loadTable();
    }

    @FXML
    private void onPrintToConsole(ActionEvent event) {
        System.out.println(mainApp.getTableData().toString());
    }

    private void loadTable() {
        TableData tableData = mainApp.getTableData();

        // define row-specific context menu
        Callback<TableView<RowData>, TableRow<RowData>> rowFactory = 
            new Callback<TableView<RowData>, TableRow<RowData>>() {
            
            @Override
            public TableRow<RowData> call(TableView<RowData> tableView) {
                final TableRow<RowData> row = new TableRow<>();

                final ContextMenu rowMenu = new ContextMenu();

                MenuItem addRowBeforeItem = new MenuItem("Add row before");
                addRowBeforeItem.setOnAction(new EventHandler<ActionEvent>() {
                        @Override
                            public void handle(ActionEvent event) {
                            int insertIdx = tableView.getItems().indexOf(row.getItem());
                            int rowSize = mainApp.getTableData().getAttributes().size();
                            
                            tableView.getItems().add(insertIdx, new RowData(rowSize));
                        }
                    });

                MenuItem addRowAfterItem = new MenuItem("Add row after");
                addRowAfterItem.setOnAction(new EventHandler<ActionEvent>() {
                        @Override
                            public void handle(ActionEvent event) {
                            int insertIdx = tableView.getItems().indexOf(row.getItem()) + 1;
                            int rowSize = mainApp.getTableData().getAttributes().size();
                            
                            tableView.getItems().add(insertIdx, new RowData(rowSize));
                        }
                    });

                MenuItem deleteRowItem = new MenuItem("Delete row");
                deleteRowItem.setOnAction(new EventHandler<ActionEvent>() {
                        @Override
                            public void handle(ActionEvent event) {
                            tableView.getItems().remove(row.getItem());
                        }
                    });

                // "Borrow" menu items from table's context menu, if there is one.
                rowMenu.getItems().addAll(addRowBeforeItem, addRowAfterItem, deleteRowItem);

                final ContextMenu tableMenu = tableView.getContextMenu();
                if (tableMenu != null) {
                    rowMenu.getItems().add(new SeparatorMenuItem());
                    rowMenu.getItems().addAll(tableMenu.getItems());
                }

                // only display context menu for non-null items:
                row.contextMenuProperty().bind(
                                               Bindings.when(Bindings.isNotNull(row.itemProperty()))
                                               .then(rowMenu)
                                               .otherwise(tableMenu));

                return row;
            }
        };

        tableView.setRowFactory(rowFactory);

        Callback<TableColumn<RowData, String>, TableCell<RowData, String>> cellFactoryForRowData = 
            new Callback<TableColumn<RowData, String>, TableCell<RowData, String>>()
            {
                @Override
                public TableCell call(TableColumn p) {
                    return new EditingCell();
                }  
            };
        
        Callback<TableColumn.CellDataFeatures<RowData, String>, ObservableValue<String>> rowDataValueFactory = 
            new Callback<TableColumn.CellDataFeatures<RowData, String>, ObservableValue<String>>() {
            @Override
            public ObservableValue<String> call(TableColumn.CellDataFeatures<RowData, String> p) {
                int cellIndex = (int) p.getTableColumn().getUserData();
                return new SimpleStringProperty(p.getValue().getValues().get(cellIndex));
            }
        };

        ObservableList<TableColumn<RowData, String>> tableCols = FXCollections.observableArrayList();
        for (int i = 0; i < tableData.getAttributes().size(); i++) {
            TableColumn<RowData, String> tmpCol = new TableColumn(tableData.getAttributes().get(i));
            tmpCol.setUserData(i);
            tmpCol.setCellFactory(cellFactoryForRowData);
            tmpCol.setCellValueFactory(rowDataValueFactory);
            tmpCol.setOnEditCommit(new EventHandler<TableColumn.CellEditEvent<RowData, String>>() {
                    @Override
                        public void handle(TableColumn.CellEditEvent<RowData, String> t) {
                        ((RowData) t.getTableView().getItems().get(
                            t.getTablePosition().getRow())
                        ).getValues().set((int) tmpCol.getUserData(), t.getNewValue());
                    }
                });

            tableCols.add(tmpCol);
        }

        tableView.getColumns().setAll(tableCols);
        tableView.setItems(tableData.getRows());
    }



}
