import styled, { css } from 'styled-components'

// Components
import Button from '../components/Button'
import Card from '../components/Card'
import List from '../components/List'
import Text from '../components/Text'
import TextInput from '../components/TextInput'

const StyledWrapper = styled.div`
  display: flex;
  align-items: center;
  flex-direction: column;
  padding: 20px;
`

const StyledCard = styled(Card)`
  width: 90%;
  height: 480px;
  background-color: transparent;
  border-radius: 4px;
  box-shadow: none;
  
  margin: 15px;

  padding: 20px;
  display: flex;
  flex-direction: column;
  justify-content: center;
  align-items: center;

  > * + * {
    margin-top: 10px;
  }
`

const Brand = styled.div`
  display: flex;
  width: 100%;

  :before {
    width: 40px; height: 40px;
    background: url("${({icon}) => icon}") no-repeat center / 100%;
    content: '';
    box-shadow: 0 4px 9px rgba(0, 161, 255, 0.33);
  }
`

const Robot = styled.img`
  height: 300px;
  width: auto;
`

const ConnectivityLabel = styled.span`
  display: flex;
  align-items: center;
  justify-content: center;

  height: 20px;
  width: 70px;
  
  ${props => props.isOnline ? css`
    background-image: linear-gradient(68deg, var(--primary), #1effc3);
    box-shadow: 0 4px 9px rgba(0, 161, 255, 0.33);
  ` : css`
    background-color: var(--danger);
    box-shadow: 0 4px 9px rgba(0, 0, 0, 0.13);
  `};

  border-radius: 10px;
  
  font-size: 12px;
  font-weight: 600;
  color: var(--gray8);

  position: absolute;
  bottom: 25px;
  left: 10px;

  :after {
      content: '${props => props.isOnline ? "Online" : "Offline"}';
  }
`

const ControllerLabel = styled.img`
  position: absolute;
  bottom: 30px;
  right: 20px;
  width: 75px;
  display: ${props => props.isVisible ? 'block' : 'none'};
`

const ProximityMeasurementLabel = styled.div`
  display: flex;
  align-items: center;
  justify-content: center;
  
  position: absolute;
  top: ${props => props.top};
  left: ${props => props.left};

  height: 25px;
  width: 60px;
  background: var(--green);

  font-weight: 600;
  color: var(--gray8);

  border-radius: 15px;

  :after{
    content: '${props => props.value} cm';
  }
`

export default { Brand, StyledWrapper, StyledCard, Robot, ProximityMeasurementLabel, ControllerLabel, ConnectivityLabel }