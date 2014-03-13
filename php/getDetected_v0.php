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
        $folder1='server_dev/data/stasm_images/';
        $folder2='server_dev/data/crop_images/';
        $folder3='server_dev/data/mesh_images/';
        $in_folder='server_dev/data/upload_images/';
   
          
        $output = shell_exec('python /var/www/php/server_dev/android/facedetect.py ' .$in_folder. $filename .' ' .$folder1. $filename .' ' .$folder2. $filename .' det');
        logfile('log.txt','output:' .$output);
                
               
        if (file_exists($folder1 .$filename)) {

        logfile('log.txt', $filename.' file exists');
    
        header('Content-Type: image/jpeg');
        readfile($folder1 .$filename);
        } else {
                logfile('log.txt','file ' .$filename .' NOT exists');
        }
     
?>
