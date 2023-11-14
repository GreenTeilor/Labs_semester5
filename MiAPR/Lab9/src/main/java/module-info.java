module by.bsuir.lab9 {
    requires javafx.controls;
    requires javafx.fxml;


    opens by.bsuir.lab9 to javafx.fxml;
    exports by.bsuir.lab9;
}