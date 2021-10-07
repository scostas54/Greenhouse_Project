<?php

$servername = "localhost";

$dbname = "greenhouse_v0";
$username = "admin";
$password = "invernadero140794";

// Keep this API Key value to be compatible with the ESP32 code provided in the project page. 
// If you change this value, the ESP32 sketch needs to match
$api_key_value = "tPmAT5Ab3j7F9";

$api_key= $location_id = $fans = $RGB = $pump_interval = $temp_threshold = $humidity_threshold = $CO2_threshold = $temp_internal = $humidity_internal = $CO2_internal = $value = "";

if ($_SERVER["REQUEST_METHOD"] == "POST") {
    $api_key = measurements_input($_POST["api_key"]);
    if($api_key == $api_key_value) {
        $location_id = measurements_input($_POST["location_id"]);
        $fans = measurements_input($_POST["fans"]);
        $RGB = measurements_input($_POST["RGB"]);
        $pump_interval = measurements_input($_POST["pump_interval"]);
        $temp_threshold = measurements_input($_POST["temp_threshold"]);
        $humidity_threshold = measurements_input($_POST["humidity_threshold"]);
        $CO2_threshold = measurements_input($_POST["CO2_threshold"]);
        $temp_internal = measurements_input($_POST["temp_internal"]);
        $humidity_internal = measurements_input($_POST["humidity_internal"]);
        $CO2_internal = measurements_input($_POST["CO2_internal"]);
        
        // Create connection
        $conn = new mysqli($servername, $username, $password, $dbname);
        // Check connection
        if ($conn->connect_error) {
            die("Connection failed: " . $conn->connect_error);
        } 
        
        $sql = "INSERT INTO measurements (location_id, fans, RGB, pump_interval, temp_threshold, humidity_threshold, CO2_threshold, temp_internal, humidity_internal, CO2_internal)
        VALUES ('" . $location_id . "', '" . $fans . "', '" . $RGB . "', '" . $pump_interval . "', '" . $temp_threshold . "', '" . $humidity_threshold . "', '" . $CO2_threshold . "', '" . $temp_internal . "', '" . $humidity_internal . "', '" . $CO2_internal . "')";
        
        if ($conn->query($sql) === TRUE) {
            echo "New record created successfully";
        } 
        else {
            echo "Error: " . $sql . "<br>" . $conn->error;
        }
    
        $conn->close();
    }
    else {
        echo "Wrong API Key provided.";
    }

}
else {
    echo "No data posted with HTTP POST.";
}

function measurements_input($data) {
    $data = trim($data);
    $data = stripslashes($data);
    $data = htmlspecialchars($data);
    return $data;
}
