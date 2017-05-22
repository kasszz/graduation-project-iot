int distance_closed = 15;
int times_open_threshold = 3;
int elevator_left_interval = 0;
int elevator_right_interval = 0;

bool check_elevator_left_open(int distance) {
  if(distance > distance_closed) {
    elevator_left_interval ++;
  } else {
    elevator_left_interval = 0;
  }

  Serial.println("Distance elevator left: ");
  Serial.print(distance);
  Serial.println("");

  Serial.println("-----------------------");

  if(elevator_left_interval >= times_open_threshold) {
    return true;
  } else {
    return false;
  }
}

bool check_elevator_right_open(int distance) {
  if(distance > distance_closed) {
    elevator_right_interval ++;
  } else {
    elevator_right_interval = 0;
  }

  Serial.println("Distance elevator right: ");
  Serial.print(distance);
  Serial.println("");

  Serial.println("-----------------------");

  if(elevator_right_interval >= times_open_threshold) {
    return true;
  } else {
    return false;
  }
}

void elevator_check() {
  if(evelator_left_turn) {
    evelator_left_turn = false;
    bool elevator_left_open = check_elevator_left_open(elevator_left_get_distance());
  
    if(elevator_left_open) {
      dormant = true;
      send_message("elevator_open", "left");
    }
  } else {
    evelator_left_turn = true;
    bool elevator_right_open = check_elevator_right_open(elevator_right_get_distance());
  
    if(elevator_right_open) {
      dormant = true;
      send_message("elevator_open", "right");        
    }
  }
}

void reset_elevator_variables() {
  elevator_left_interval = 0;
  elevator_right_interval = 0; 
}

