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

$sql = "SELECT id, sensor, module, shelve, sector, value, reading_time FROM CO2 ORDER BY id DESC";

echo '<head>
        <title><CO2></title>
    </head>';

echo '<table cellspacing="5" cellpadding="5">
      <tr> 
        <td>ID</td> 
        <td>Sensor</td> 
        <td>Module</td> 
        <td>Shelve</td> 
        <td>Sector</td>
        <td>Value</td> 
        <td>Timestamp</td> 
      </tr>';
 
if ($result = $conn->query($sql)) {
    while ($row = $result->fetch_assoc()) {
        $row_id = $row["id"];
        $row_sensor = $row["sensor"];
        $row_module = $row["module"];
        $row_shelve = $row["shelve"];
        $row_sector = $row["sector"]; 
        $row_value = $row["value"]; 
        $row_reading_time = $row["reading_time"];
        // Uncomment to set timezone to - 1 hour (you can change 1 to any number)
        //$row_reading_time = date("Y-m-d H:i:s", strtotime("$row_reading_time - 1 hours"));
      
        // Uncomment to set timezone to + 4 hours (you can change 4 to any number)
        //$row_reading_time = date("Y-m-d H:i:s", strtotime("$row_reading_time + 4 hours"));
      
        echo '<tr> 
                <td>' . $row_id . '</td> 
                <td>' . $row_sensor . '</td> 
                <td>' . $row_module . '</td> 
                <td>' . $row_shelve . '</td> 
                <td>' . $row_sector . '</td>
                <td>' . $row_value . '</td> 
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