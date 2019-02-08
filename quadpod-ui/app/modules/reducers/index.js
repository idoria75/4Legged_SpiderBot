import { 
  ROBOT_STATE_UPDATE,
  CONTROLLER_STATE_UPDATE,
  CONNECTION_STATE_UPDATE
} from '../actions';

const initialState = {
  distances: {
    front: 0.0,
    left: 0.0,
    back: 0.0,
    right: 0.0,
  },
  isRobotOnline: false,
  isControllerConnected: false,
};

export default function rootReducer(state = initialState, action) {
  switch (action.type) {
    case ROBOT_STATE_UPDATE:
      return {...state, distances: action.state.sensors}
    case CONTROLLER_STATE_UPDATE:
      return {...state, isControllerConnected: action.state.isControllerConnected}
    case CONNECTION_STATE_UPDATE:
      return {...state, isRobotOnline: action.state.isOpen}
    default:
      return state;
  }
};
