<!DOCTYPE html>
<html>
<head>
<title>Lab 2</title>
</head>
<body>

<form action="" method="POST">
Name: 
<input type="text" name="name"><br>
<input type="radio" name="Major" value="Computer Science">Computer Science<br>
<input type="radio" name="Major" value="Other">Other<br>
<select name="year">
<option value="F">Freshman</option>
<option value="S">Sophomore</option>
<option value="J">Junior</option>
<option value="Se">Senior</option>
</select><br>
<input type="submit" name="submit" value="Submit">
</form>

<?php
if(isset($_POST['submit'])){
	echo "Name: " .  $_POST['name'] . "<br>";
	echo "Major: " . $_POST['Major'] . "<br>";
	switch($_POST['year']){
		case "F":
			echo "Year: Freshman";
			break;
		case "S":
			echo "Year: Sophomore";
			break;
		case "J":
			echo "Year: Junior";
			break;
		case "Se":
			echo "Year: Senior";
			break;

}
}
?>
