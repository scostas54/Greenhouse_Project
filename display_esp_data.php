<!DOCTYPE html>
<html><body>
<?php

$servername = "localhost";

$dbname = "greenhouse_v0";
$username = "admin";
$password = "invernadero140794";

// Create connection
$conn = new mysqli($servername, $username, $password, $dbname);
// Check connection
if ($conn->connect_error) {
    die("Connection failed: " . $conn->connect_error);
} 

$sql = "SELECT id, location_id, fans, RGB, pump_interval, temp_threshold, humidity_threshold, CO2_threshold, temp_internal, humidity_internal,
        , CO2_internal, reading_time FROM CO2 ORDER BY id DESC";

echo '<head>
        <title><Measurements></title>
    </head>';

echo '<table cellspacing="5" cellpadding="5">
      <tr> 
        <td>ID</td> 
        <td>Location ID</td> 
        <td>Fans</td> 
        <td>RGB</td> 
        <td>Pump Interval(ms)</td>
        <td>Temp Threshold</td>
        <td>Humidity Threshold</td>
        <td>CO2 Threshold</td>
        <td>Temp Internal</td>
        <td>Humidity Internal</td>
        <td>CO2 Internal</td>
        <td>Timestamp</td> 
      </tr>';
 
if ($result = $conn->query($sql)) {
    while ($row = $result->fetch_assoc()) {
        $row_id = $row["id"];
        $row_location_id = $row["location_id"];
        $row_fans = $row["fans"];
        $row_RGB = $row["RGB"];
        $row_pump_interval = $row["pump_interval"]; 
        $row_temp_threshold = $row["temp_threshold"];
        $row_humidity_threshold = $row["humidity_threshold"];
        $row_CO2_threshold = $row["CO2_threshold"];
        $row_temp_internal = $row["temp_internal"];
        $row_humidity_internal = $row["humidity_internal"];
        $row_CO2_internal = $row["CO2_internal"];
        $row_reading_time = $row["reading_time"];
        // Uncomment to set timezone to - 1 hour (you can change 1 to any number)
        //$row_reading_time = date("Y-m-d H:i:s", strtotime("$row_reading_time - 1 hours"));
      
        // Uncomment to set timezone to + 4 hours (you can change 4 to any number)
        //$row_reading_time = date("Y-m-d H:i:s", strtotime("$row_reading_time + 4 hours"));
      
        echo '<tr> 
                <td>' . $row_id . '</td> 
                <td>' . $row_location_id . '</td> 
                <td>' . $row_fans . '</td> 
                <td>' . $row_RGB . '</td> 
                <td>' . $row_pump_interval . '</td>
                <td>' . $row_temp_threshold . '</td>
                <td>' . $row_humidity_threshold . '</td>
                <td>' . $row_CO2_threshold . '</td>
                <td>' . $row_temp_internal . '</td>
                <td>' . $row_humidity_internal . '</td>
                <td>' . $row_CO2_internal . '</td>                
                <td>' . $row_reading_time . '</td> 
              </tr>';
    }
    $result->free();
}

$conn->close();
?> 
</table>
</body>
</html>
