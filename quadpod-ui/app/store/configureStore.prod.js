// @flow
import { createStore } from 'redux';
import rootReducer from '../modules/reducers';

function configureStore(initialState) {
  return createStore(rootReducer, initialState);
}

export default { configureStore };