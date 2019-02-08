import React from 'react';
import { render } from 'react-dom';
import { AppContainer } from 'react-hot-loader';
import Modal from 'react-modal'
import Root from './containers/Root';
import { configureStore } from './store/configureStore';
import './app.global.css';

const store = configureStore();

Modal.setAppElement('#root')

render(
  <AppContainer>
    <Root store={store} />
  </AppContainer>,
  document.getElementById('root')
);

if (module.hot) {
  module.hot.accept('./containers/Root', () => {
    const NextRoot = require('./containers/Root'); // eslint-disable-line global-require
    render(
      <AppContainer>
        <NextRoot store={store} />
      </AppContainer>,
      document.getElementById('root')
    );
  });
}
