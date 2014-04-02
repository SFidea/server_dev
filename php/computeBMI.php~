<?php
        //log function
        function logFile($filename,$msg){
	$fd = fopen($filename,"a");
	$str = "[".date("Y/m/d h:i:s",time())."]".$msg;
	fwrite($fd, $str."\n");
	fclose($fd);
        }

        $tokens=explode('/', $_GET['name']);
        $filename=$tokens[sizeof($tokens)-1];
        $folder='server_dev/data/upload_images/';
            
        if (file_exists($folder .$filename)) {

        logfile('log.txt', $filename.' file exists');

	//compute bmi feature
    	$cmd='./server_dev/computeBMI/Debug/computeBMI '.$folder .$filename .' /home/user/Desktop/stasm/stasm4.1.0/data/';
	$shell_output = shell_exec($cmd);
	//echo $shell_output;
	$shell_output = '1 ' .$shell_output;
	$test_file = 'server_dev/BMI_SVM/test.txt';
	// Open the file to get existing content
	// Write the contents back to the file
	file_put_contents($test_file, $shell_output);	

	//compute bmi using svm
	$model_file = 'server_dev/BMI_SVM/bmi_data.model';
	$output_file = 'server_dev/BMI_SVM/bmi_output';
	$cmd_svm='./server_dev/BMI_SVM/libsvm/svm-predict ' .$test_file.' '. $model_file.' '. $output_file;
	//echo $cmd_svm;
	$shell_output_svm = shell_exec($cmd_svm);
	$res=file_get_contents($output_file, $shell_output);	

	$res = substr($res,0,-1);
	$json = array('bmi'=>$res);
	$jsonstring = json_encode($json);
	echo $jsonstring;

        } else {
                logfile('log.txt','computeBMI.php: file ' .$folder .$filename .' NOT exists');
        }

?>
