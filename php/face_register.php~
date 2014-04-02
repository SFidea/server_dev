<?php
//log function
function logFile($filename,$msg){
	$fd = fopen($filename,"a");
	$str = "[".date("Y/m/d h:i:s",time())."]".$msg;
	fwrite($fd, $str."\n");
	fclose($fd);
        }


//Save json string into image(jpg)
function base64_to_jpeg2($img, $output_file) {
	$img = str_replace('data:image/jpg;base64,', '', $img);
	$img = str_replace(' ', '+', $img);
	$data = base64_decode($img);
	$success = file_put_contents($output_file, $data);
}


if (!empty($HTTP_RAW_POST_DATA)){
    logFile('log.txt',"Getting POST Object");
    $data = json_decode($HTTP_RAW_POST_DATA,true); //decode json object

    $folder = "/var/www/php/server_dev/data/register_images/"; // output image folder

    if (!file_exists($folder.$data["name"])) { //create folder name = data["name"]
        logFile('log.txt',"Creating folder ".$data["name"]);
        mkdir($folder.$data["name"]);
    }

    //Save image
    $folder=$folder.$data["name"].'/';
    $output_file=$folder.'IMG_'.date('Ymd_His',time()).'.jpg';
    base64_to_jpeg2($data["image"], $output_file);

    //Save label infomation (json string)
    if (!file_exists($folder.'/label')) {
        $output_label=$folder.'/label';
	$label_data = array("name"=>$data["name"],"gender"=>$data["gender"],"race"=>$data["race"],"age"=>$data["age"]);
	$json_label = json_encode($label_data);
        $success = file_put_contents($output_label, $json_label);
    }	
}

$res = "Success";
$response=json_encode(array("res"=>$res));
echo $response;

?>




