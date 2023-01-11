<?php

/*
  Rui Santos
  Complete project details at https://RandomNerdTutorials.com/esp32-esp8266-mysql-database-php/
  
  Permission is hereby granted, free of charge, to any person obtaining a copy
  of this software and associated documentation files.
  
  The above copyright notice and this permission notice shall be included in all
  copies or substantial portions of the Software.
*/

$servername = "localhost";

// REPLACE with your Database name
$dbname = "id20040674_terserahwes";
// REPLACE with Database user
$username = "id20040674_miniproyek";
// REPLACE with Database user password
$password = "N{&X@MVcY]vx7S4w";

// Keep this API Key value to be compatible with the ESP32 code provided in the project page. 
// If you change this value, the ESP32 sketch needs to match
$api_key_value = "tPmAT5Ab3j7F9";

$api_key= $id = $nama = $no_kartu = $tanggal = $jam_masuk = "";

if ($_SERVER["REQUEST_METHOD"] == "POST") {
    $api_key = test_input($_POST["api_key"]);
    if($api_key == $api_key_value) {
        $id = test_input($_POST["id"]);
        $nama = test_input($_POST["nama"]);
        $no_kartu = test_input($_POST["no_kartu"]);
        $tanggal = test_input($_POST["tanggal"]);
        $jam_masuk = test_input($_POST["jam_masuk"]);
        
        // Create connection
        $conn = new mysqli($servername, $username, $password, $dbname);
        // Check connection
        if ($conn->connect_error) {
            die("Connection failed: " . $conn->connect_error);
        } 
        
        $sql = "INSERT INTO mahasiswa (id, nama, no_kartu, tanggal, jam_masuk)
        VALUES ('" . $id . "', '" . $nama . "', '" . $no_kartu . "', '" . $tanggal . "', '" . $jam_masuk . "')";
        
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

function test_input($data) {
    $data = trim($data);
    $data = stripslashes($data);
    $data = htmlspecialchars($data);
    return $data;
}