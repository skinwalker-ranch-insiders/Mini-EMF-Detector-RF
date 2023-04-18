<?php include '/var/www/include/index.inc'; ?>
<html> <title>EMF 1 Data Logger</title> <style> table, th, td {
  border: 1px solid black;
}
</style>
<body>
<?php
$curr_wind = date('Y-m-d');
//$curr_wind = "2023-04-10";
//echo $curr_wind;
//echo "<br> \n";
$reads = get_EMF_reads($curr_wind);

?>
<h2>External Sensors</h2>

<table style="width:50%">
	<tr>
		<th><font size="8">Sensor</font></th>
		<th><font size="8">Timestamp</font></th> 
		<th><font size="8">Sensor Value</font></th>
	</tr>
	<?php
	echo "\n";
	for ($rd=0; $rd<10;$rd++)
		{
		echo "\t<tr> \n";
		echo "\t\t<td align=center><font size=6>";
		printf("%s",$reads[$rd][0]);;
		echo "</font> \n";
		echo "\t\t</td> \n";
		echo "\n";
		echo "\t\t<td align=center><font size=6>";
		printf("%s",$reads[$rd][1]);
		echo "</font> \n";
		echo "\t\t</td> \n";
		echo "\n";
		echo "\t\t<td align=center><font size=6>";
		printf("%s",$reads[$rd][2]);
		echo "</font> \n";
		echo "\t\t</td> \n";
		echo "\t</tr> \n";
		}

	echo "</table> \n";

//$myFile = '/home/johns/EMF/EMF1_log.txt';
//$lines = file('/home/johns/EMF/EMF1_log.txt');
//$count = 0;
//foreach($lines as $line) {
//    $count += 1;
//    echo $line. "<br>";
//}
?>
</body>
</html>
