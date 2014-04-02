<?php
/**
 * Returns the latitude and longitude of a location
 */
function get_latitude_longitude($add){
        $prepAddr = str_replace(' ','+',$add);
        $geocode=file_get_contents('http://maps.google.com/maps/api/geocode/json?address='.$prepAddr.'&sensor=false');
        $output= json_decode($geocode);
  		$lat_lng = array (
		 'lat' => $output->results[0]->geometry->location->lat,
		 'lng' => $output->results[0]->geometry->location->lng,
			);
        return $lat_lng;
}
/**
 * Updates the selected location in the table = 'osmap'. 
 */
function id_to_arg($variable){
  if ($variable != '%') {
     return $variable;
  }
 } 
 
 /**
 * Creates table header for location display. 
 */
 function create_table_header(){
  return $header = array(
					array('data' => 'Name',     'field' => 'name', 'sort' => 'asc'),
					array('data' => 'Address',  'field' => 'address'),
					array('data' => 'Type', 'field' => 'type', 'sort' => 'asc'),
					array('data' => 'Delete'),
					array('data' => 'Edit'),				
				);
}
/**
* Returns type list for colored markers on the map. 
*/
function type_list(){
  return array("university" => 'university', 
               "business" => 'business', 
			   "office" =>'office', 
			   "library" => 'library',
			   "shopping"=>'shopping');
}
function create_delete_form($form, $form_state){
 $form['delete']['confirm'] = array(
  '#markup' => '<p>Please confirm if you would like to continue with the delete operation</p>'
  );
  
 $form['submit'] =array (
       '#type' => 'submit',
	   '#value' => 'Delete'
	   );
	  
 $form['cancel'] = array(
      '#type' => 'button',
      '#value' => 'CANCEL',
      '#validate' => array(),
         '#attributes' => array(
            'onClick' => 'history.go(-1); return true;'),
		'#post_render' => array('change_button_type'),	
		  
    ); 
  
return $form;
 
}
/**
* creates a form for adding and updating locations 
*/
function create_form($form, $form_type, $id){
 $typeOptions = type_list();
  if ($form_type == 'add'){
    $form[$form_type] = array(
      '#type' => 'fieldset', //container for multiple fields
	  '#title' => t('Add new Location'),
    );
  }
  else
  {
    $form[$form_type] = array(
    '#type' => 'fieldset', //container for multiple fields
	'#title' => 'Update existing location',
  );
  }
  
  $form[$form_type]['name'] = array(
    '#type' => 'textfield' ,
	'#title' =>'Name',
	'#required' => TRUE,
	'#attributes' =>array('placeholder' => t('Harvard Web Publishing')),
	'#size' => 40,
  );
  $form[$form_type]['address'] = array(
    '#type' => 'textfield',
	'#title' => 'Address',
	'#required' => TRUE,
	'#attributes' =>array('placeholder' => t('125 Mount Auburn Street, Cambridge, MA')),
	'#size' => 50,
  ); 
  $form[$form_type]['type'] = array(
   '#type' => 'select',
   '#title' => 'Type',
   '#options' => $typeOptions,
   '#required' => TRUE,
   '#default_value' => $typeOptions['university'],
  );
  $form['id'] = array (
    '#type' => 'value',
	'#value' => $id  
  );
  
   if ($form_type == 'add'){
    $form['submit'] =array (
       '#type' => 'submit',
	   '#value' => 'ADD'
	   );
	 }
	else {
	   $form['submit'] =array (
           '#type' => 'submit',
	       '#value' => 'UPDATE'
		   );
	   } 
	  
	 $form['cancel'] = array(
      '#type' => 'button',
      '#value' => 'CANCEL',
      '#validate' => array(),
	//  '#href' => 'testmap/list'
         '#attributes' => array(
            'onClick' => 'history.go(-1); return true;'),
		'#post_render' => array('change_button_type'),	
		  
    ); 
  
return $form;
}
function change_button_type($markup, $element) {
    $markup = str_replace('type="submit', 'type="button', $markup);
    return $markup;
}

/*
* creates and returns array of map values
*/
function return_map_values($name,$address,$type,$lat,$lng){
  return $mapValue = array (
	    'name' => $name,
		'address' => $address,
		'type' => $type,
		'lat' => $lat,
		'lng' => $lng
		);
}
/*
* creates and returns mal values in a table
*/
 function create_map_table($mapValues){
  $output ='';
  $location = array();
  try {  
        if ($mapValues){
          $rows = array();
	    //  $header = array(t('Name'),t('Address'), t('Lat'), t('Lng'),t('Type'), t('Delete'), t('Edit'));
	      $header = array(
           array('data' =>'Name', 'field' => 'name', 'sort' => 'ASC'),
		   array('data' =>'Address' , 'field' => 'address'),
		   array('data' =>'Latitutde' , 'field' =>'lat'),
		   array('data' =>'Longitude' , 'field' =>'lng'),
		   array('data' =>'Type', 'field' =>'type'),   
		   array('data' => 'Delete'),
		   array('data' => 'Edit'),
           );		  
    	   foreach ($mapValues as $mapValue){
		        
	            $options = array('query' => drupal_get_destination(),);
                $rows[] = array(
                       $mapValue->name, 
					   $mapValue->address,
					   $mapValue->lat,
					   $mapValue->lng,
					   $mapValue->type,
                       l(t('Delete'), "testmap/delete/".$mapValue->id,$options),
					   l(t('Edit'), "testmap/update/".$mapValue->id)				   
					   
                );
            }
	     $output .= theme('table', array('header' => $header, 'rows'=>$rows));
	   }
	}
	catch (Exception $e){
	  drupal_set_message(t('Failed to create map table. Message = %message, query=%query', 
	       array('%message' =>$e->getMessage(),'%query' => $e->query_string)), 'error');
	 }
	return $output;
 
 } 
