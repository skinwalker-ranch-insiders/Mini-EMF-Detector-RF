<?php
function get_EMF_reads($curr_wind)
	{
	$dbname         = "sensors";
	$dbserver       = "localhost";
	$dbuser         = "MySQL Username";
	$dbpass         = "MySQL Password";

	$DB_Link = new mysqli($dbserver, $dbuser, $dbpass, $dbname);
	//echo $DB_Link->host_info . "<br>\n";

	if($DB_Link->connect_errno ) {
            printf("Connect failed: %s<br />", $DB_Link->connect_error);
            exit();
         }
        //printf('Connected successfully.<br />');
	
	$get_read_query = "select Sensor_ID, Event_DateTime, Sensor_Value from detectors where Event_DateTime like '$curr_wind%' order by Event_DateTime DESC limit 10;";
	//echo $get_read_query;
	//echo "<br> \n";	
	$get_read_result = mysqli_query($DB_Link,$get_read_query);
	//$read_results = mysqli_fetch_array($get_read_result);

	$r=0;
	while ($row=mysqli_fetch_assoc($get_read_result))
		{
		$read_results[$r][0] = $row["Sensor_ID"];
		$read_results[$r][1] = $row["Event_DateTime"];
		$read_results[$r][2] = $row["Sensor_Value"];
		$r++;
		}

	return($read_results);
	}
?>