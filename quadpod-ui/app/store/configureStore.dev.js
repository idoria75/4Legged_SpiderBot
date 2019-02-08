import { createStore, applyMiddleware, compose } from 'redux';
import { createLogger } from 'redux-logger';
import thunk from 'redux-thunk';
import * as actions from '../modules/actions';
import rootReducer from '../modules/reducers';

const configureStore = (initialState?) => {
  
  // Redux Configuration
  const middleware = [thunk];
  const enhancers = [];

  // Logging Middleware
  const logger = createLogger({
    level: 'info',
    collapsed: true
  });

  // Skip redux logs in console during the tests
  if (process.env.NODE_ENV !== 'test') {
    middleware.push(logger);
  }

  // Redux DevTools Configuration
  const actionCreators = {
    ...actions
  };
  // If Redux DevTools Extension is installed use it, otherwise use Redux compose
  /* eslint-disable no-underscore-dangle */
  const composeEnhancers = window.__REDUX_DEVTOOLS_EXTENSION_COMPOSE__
    ? window.__REDUX_DEVTOOLS_EXTENSION_COMPOSE__({
        // Options: http://extension.remotedev.io/docs/API/Arguments.html
        actionCreators
      })
    : compose;
  /* eslint-enable no-underscore-dangle */

  // Apply Middleware & Compose Enhancers
  enhancers.push(applyMiddleware(...middleware));
  const enhancer = composeEnhancers(...enhancers);

  // Create Store
  const store = createStore(rootReducer, initialState, enhancer);

  if (module.hot) {
    module.hot.accept(
      '../modules/reducers',
      () => store.replaceReducer(require('../modules/reducers')) // eslint-disable-line global-require
    );
  }

  return store;
};

export default { configureStore };
