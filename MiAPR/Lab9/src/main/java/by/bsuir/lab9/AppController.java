package by.bsuir.lab9;

import javafx.beans.binding.Bindings;
import javafx.beans.property.SimpleStringProperty;
import javafx.beans.value.ObservableValue;
import javafx.collections.FXCollections;
import javafx.collections.ObservableList;
import javafx.event.ActionEvent;
import javafx.fxml.FXML;
import javafx.fxml.Initializable;
import javafx.scene.control.Button;
import javafx.scene.control.ComboBox;
import javafx.scene.control.Label;
import javafx.scene.control.TableColumn;
import javafx.scene.control.TableView;
import javafx.scene.control.cell.PropertyValueFactory;
import javafx.scene.control.cell.TextFieldTableCell;
import javafx.util.Callback;

import java.net.URL;
import java.text.DecimalFormat;
import java.text.DecimalFormatSymbols;
import java.util.Collections;
import java.util.Comparator;
import java.util.HashMap;
import java.util.Map;
import java.util.ResourceBundle;
import java.util.stream.IntStream;

public class AppController implements Initializable {

    @FXML
    private Button btnCalculate;

    @FXML
    private Button btnClassificate;

    @FXML
    private ComboBox<Integer> cbAttributes;

    @FXML
    private ComboBox<Integer> cbClasses;

    @FXML
    private Label lbResult;

    @FXML
    private Label lbSample;

    @FXML
    private TableView<?> tvObject;

    @FXML
    private TableView<Obj> tvResult;

    @FXML
    private TableView<Obj> tvSample;

    ObservableList<Obj> objs = FXCollections.observableArrayList(
            new Obj("Класс 1", new HashMap<>(Map.of(1, 1.0, 2, 2.0, 3, 3.0))),
            new Obj("Класс 2", new HashMap<>(Map.of(1, 1.0, 2, 2.0, 3, 3.0))),
            new Obj("Класс 3", new HashMap<>(Map.of(1, 1.0, 2, 2.0, 3, 3.0))),
            new Obj("Класс 4", new HashMap<>(Map.of(1, 1.0, 2, 2.0, 3, 3.0))),
            new Obj("Класс 5", new HashMap<>(Map.of(1, 1.0, 2, 2.0, 3, 3.0)))
    );

    @FXML
    void onBtnCalculateClick(ActionEvent event) {
        //Here actions on calculate weights
    }

    @FXML
    void onBtnClassificateClick(ActionEvent event) {
        //Here actions on classification
    }

    @FXML
    void onCbClassesMouseClick() {
        //Here actions on change classes number
        recreateTable(cbClasses.getValue(), objs.get(0).getAttributes().size());
    }

    @FXML
    void onCbAttributesMouseClick() {
        //Here actions on change attributes number
        recreateTable(objs.size(), cbAttributes.getValue());
    }

    @FXML
    @Override
    public void initialize(URL url, ResourceBundle resourceBundle) {
        //Add digits to cbClasses
        cbClasses.getItems().clear();
        cbClasses.getItems().addAll(IntStream.rangeClosed(Const.MIN_CLASSES, Const.MAX_CLASSES).boxed().toList());

        //Add digits to cbAttributes
        cbAttributes.getItems().clear();
        cbAttributes.getItems().addAll(IntStream.rangeClosed(Const.MIN_ATTRIBUTES, Const.MAX_ATTRIBUTES).boxed().toList());

        recreateTable(5, 4);
    }

    private void recreateTable(int classesAmount, int attributesAmount) {
        //Create new data for table
        ObservableList<Obj> objs = FXCollections.observableArrayList();
        for (int i = 0; i < classesAmount; ++i) {
            Map<Integer, Double> attributes = new HashMap<>();
            for (int j = 0; j < attributesAmount; ++j) {
                attributes.put(j + 1, (double) j);
            }
            objs.add(new Obj("Класс " + (i + 1), attributes));
        }
        this.objs = objs;
        tvSample.getColumns().clear();
        tvSample.setItems(objs);

        //Some properties to make editable and resizable table
        tvSample.setEditable(true);
        tvSample.setFixedCellSize(30);
        tvSample.prefHeightProperty().bind(tvSample.fixedCellSizeProperty().multiply(Bindings.size(tvSample.getItems()).add(1.65)));
        tvSample.minHeightProperty().bind(tvSample.prefHeightProperty());
        tvSample.maxHeightProperty().bind(tvSample.prefHeightProperty());

        //Add class column
        TableColumn<Obj, String> classColumn = new TableColumn<>("Класс");
        classColumn.setCellValueFactory(new PropertyValueFactory<>("className"));
        classColumn.setOnEditCommit(
                t -> t.getTableView().getItems().get(t.getTablePosition().getRow()).setClassName(t.getNewValue())
        );
        tvSample.getColumns().add(classColumn);

        //Attributes column(which contains columns with all attributes)
        TableColumn<Obj, String> attributesColumn = new TableColumn<>("Признаки");
        attributesColumn.setCellFactory(TextFieldTableCell.forTableColumn());
        attributesColumn.setOnEditCommit(
                t -> t.getTableView().getItems().get(t.getTablePosition().getRow()).setClassName(t.getNewValue())
        );

        //Formatter to output doubles in format: "^\\d+\\.\\d+$", 1.45, 6.78 etc.
        DecimalFormatSymbols decimalFormatSymbols = DecimalFormatSymbols.getInstance();
        decimalFormatSymbols.setDecimalSeparator('.');
        DecimalFormat formatter = new DecimalFormat("0.00", decimalFormatSymbols);

        //Add each attribute
        tvSample.getColumns().add(attributesColumn);
        Callback<TableColumn.CellDataFeatures<Obj, String>, ObservableValue<String>> callBack =
                param -> param.getValue().getAttributes().containsKey(
                        (int) param.getTableColumn().getUserData())
                        ? new SimpleStringProperty(formatter.format(1d * param.getValue().getAttributes().get(
                        (int) param.getTableColumn().getUserData())))
                        : new SimpleStringProperty("");

        ObservableList<TableColumn<Obj, String>> attributeColumns = FXCollections.observableArrayList();
        Obj obj = Collections.max(objs, Comparator.comparing(c -> c.getAttributes().size()));
        for (int i = 1; i <= obj.getAttributes().size(); i++) {
            TableColumn<Obj, String> tmpCol = new TableColumn<>(String.valueOf(i));
            tmpCol.setUserData(i);
            tmpCol.setCellValueFactory(callBack);
            tmpCol.setCellFactory(TextFieldTableCell.forTableColumn());
            tmpCol.setOnEditCommit(
                    t -> {
                        t.getTableView().getItems().get(t.getTablePosition().getRow()).setClassName(t.getNewValue());
                        objs.get(t.getTablePosition().getRow()).getAttributes().
                                put(Integer.valueOf(t.getTableColumn().getText()), Double.valueOf(t.getNewValue()));
                    }
            );
            attributeColumns.add(tmpCol);
        }
        attributesColumn.getColumns().addAll(attributeColumns);
    }
}
