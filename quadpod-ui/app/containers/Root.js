import React, { Component } from 'react';
import { Provider } from 'react-redux';
import { Router } from "@reach/router"
import routes from '../constants/routes.json';

import App from './App'
import HomePage from "./HomePage";

export default class Root extends Component<Props> {
  render() {
    const { store } = this.props;
    return (
      <Provider store={store}>
           <App>
              <Router>
                <HomePage path={routes.HOME} default/>
              </Router>
            </App>
      </Provider>
    );
  }
}
