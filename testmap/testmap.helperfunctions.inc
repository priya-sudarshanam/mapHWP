<?php
/**
 * Returns the latitude and longitude of a location
 */
function get_latitude_longitude($add){
   try {
        $prepAddr = str_replace(' ','+',$add);
        $geocode=file_get_contents('http://maps.google.com/maps/api/geocode/json?address='.$prepAddr.'&sensor=false');
        $output= json_decode($geocode);
  		$lat_lng = array (
		 'lat' => $output->results[0]->geometry->location->lat,
		 'lng' => $output->results[0]->geometry->location->lng,
			);
	 }
	catch (Exception $e) {
	   drupal_set_message(t('Issue in retrieving the location data. Message = %message, query=%query', 
	           array('%message' =>$e->getMessage(),'%query' => $e->query_string)), 'error');	
	}
      return $lat_lng;
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
  return array("office" => 'office', 
			   "library" => 'library',
			   "school"  => 'school',
			   "museum" => 'museum',
			   "shopping"=>'shopping');
}
/**
* Returns delete form after user clicks on delete link in the table. 
*/
function create_delete_form($form, $form_state){
 $locationDetails = map_select_data_id($form_state['id']);
 
 $form['delete']['confirm'] = array(
  '#markup' => '<p>Are you sure you want to <font color="red">delete</font> location '.$locationDetails['name']. ' ?</p>'
  );
  
 $form['submit'] =array (
       '#type' => 'submit',
	   '#value' => 'DELETE'
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
function create_form($form, $form_state, $form_type){
 $values = map_select_data_id($form_state['id']);
  
 $typeOptions = type_list();
  if ($form_type == 'add'){
    $form[$form_type] = array(
      '#type' => 'fieldset', 
	  '#title' => t('Add new Location'),
    );
  }
  else
  {
    $form[$form_type] = array(
    '#type' => 'fieldset', 
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
  
  if ($form_type == 'update'){
    $form['existing_values'] = array(
      '#type' => 'fieldset', //container for multiple fields
	  '#title' => t('Existing Values'),
    );
     $form['existing_values']['name'] = array (
	   '#type' => 'item',
	   '#title' => 'Name',
	   '#markup' =>  $values['name']
	 );
	 
	 $form['existing_values']['address'] = array (
	   '#type' => 'item',
	   '#title' => 'Address',
	   '#markup' =>  $values['address']
	 );
	 
	 $form['existing_values']['type'] = array (
	   '#type' => 'item',
	   '#title' => 'Type',
	   '#markup' =>  $values['type']
	 );
  }
  
  
   
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
	     '#attributes' => array(
            'onClick' => 'history.go(-1); return true;'),
		'#post_render' => array('change_button_type'),	
		  
    ); 
  
return $form;
}

/**
* changes button type 
*/
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
* creates and returns map values in a table
*/
 function create_map_table(){
   ctools_include('ajax');
   ctools_include('modal');
   ctools_modal_add_js();
  $output ='';
  try {
		$add_button = make_button('Add');
		$links[] = drupal_render($add_button);
   
		$header = create_table_header();
		$rows =array();
		$map_data = paging_map_data();
		foreach($map_data as $result) {
			$rows[] = array(
			'class' => array('location-row' => 'location-row-'. $result->id),
			'data' => array(
			$result->name,
			$result->address,
			$result->type,
			ctools_ajax_text_button(t('Delete'), 'testmap/delete/nojs/'.$result->id, t('Delete this location')),
			ctools_ajax_text_button(t('Update'), 'testmap/update/nojs/'.$result->id, t('Update this location')),
				),
			); 
		} 
		$output = theme('item_list', array('items' => $links));
		$output .=  theme('table', array('header' => $header, 'rows' => $rows, 'class' => 'locations-table'));
		$output .= theme('pager');
	}
	catch (Exception $e){
	  drupal_set_message(t('Failed to create map table. Message = %message, query=%query', 
	       array('%message' =>$e->getMessage(),'%query' => $e->query_string)), 'error');
	 }
	return $output;
 
 } 
   
 function make_button($value=NULL,$id=NULL, $class=NULL) {
  $form = array();
  $form['url'] = array(
    '#type' => 'hidden',
    '#attributes' => array('class' => array('testmap-add-button-url')),
    '#value' => url('testmap/add/nojs'),
  );
   $form['ajax_button'] = array(
    '#type' => 'button',
    '#value' => 'Add new location',
    '#attributes' => array('class' => array('ctools-use-modal')),
    '#id' => 'testmap-add-button',
	);
   
   return $form;
}
