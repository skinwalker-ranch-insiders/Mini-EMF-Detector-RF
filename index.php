<?php include '/var/www/include/index.inc'; ?> <html> <title>EMF 1 Data Logger</title> <style> table, th, td {
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

echo "<h2>External Sensor Data for " . $curr_wind;
echo "\n";
?>

<table style="width:50%">
	<tr>
		<th><font size="8">Sensor</font></th>
		<th><font size="8">Timestamp</font></th> 
		<th><font size="8">Sensor Value</font></th>
		<th><font size="8">Derived mg</font></th>
		<th><font size="8">Derived uT</font></th>
	</tr>
	<?php
	echo "\n";
	$numofrecs = sizeof($reads);

	for ($rd=0; $rd<$numofrecs;$rd++)
		{
		echo "\t<tr> \n";
		echo "\t\t<td align=center><font size=6>";
		printf("%s",$reads[$rd][0]);
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
		echo "\n";
		echo "\t\t<td align=center><font size=6>";
		printf("%.2f mg",$reads[$rd][3]);
		echo "</font> \n";
		echo "\t\t</td> \n";
		echo "\t\t<td align=center><font size=6>";
		printf("%.2f uT",$reads[$rd][4]);
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
