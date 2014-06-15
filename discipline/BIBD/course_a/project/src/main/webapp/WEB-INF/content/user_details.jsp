<%@ page language="java" contentType="text/html; charset=UTF-8" pageEncoding="UTF-8"%>

<h1>${bicycle.manufacturer} ${bicycle.productName}</h1>

<div class="container-2 center">
  <img class="detail-image" src="${pageContext.request.contextPath}/resources/${bicycle.photoPath}">

  <div class="detail-category">Общая информация</div>
  <table class="detail-parameters">
    <tbody>
      <tr>
        <td class="detail-parameter"><span class="bold">Класс:</span></td>
        <td class="detail-value">${bicycle.type}</td>
      </tr>
      <tr>
        <td class="detail-parameter"><span class="bold">Год выпуска:</span></td>
        <td class="detail-value">${bicycle.year}</td>
      </tr>
      <tr>
        <td class="detail-parameter"><span class="bold">Гарантия:</span></td>
        <td class="detail-value">${bicycle.guarantee}</td>
      </tr>
    </tbody>
  </table>

  <div class="detail-category">Ходовая часть</div>
  <table class="detail-parameters">
    <tbody>
      <tr>
        <td class="detail-parameter"><div class="bold">Размер рамы:</div></td>
        <td class="detail-value">${bicycle.size}</td>
      </tr>
      <tr>
        <td class="detail-parameter"><span class="bold">Материал рамы:</span></td>
        <td class="detail-value">${bicycle.frameMaterial}</td>
      </tr>
      <tr>
        <td class="detail-parameter"><span class="bold">Цвет рамы:</span></td>
        <td class="detail-value">${bicycle.color}</td>
      </tr>     
      <tr>
        <td class="detail-parameter"><span class="bold">Тип вилки:</span></td>
        <td class="detail-value">${bicycle.fork}</td>
      </tr>
      <tr>
        <td class="detail-parameter"><span class="bold">Ход вилки:</span></td>
        <td class="detail-value">${bicycle.forkMove} мм</td>
      </tr>
      <tr>
          <td class="detail-parameter"><span class="bold">Блокировка вилки:</span></td>
          <td class="detail-value">${bicycle.lockout}</td>
      </tr>
      <tr>
        <td class="detail-parameter"><span class="bold">Диаметр колес:</span></td>
        <td class="detail-value">${bicycle.wheelsDiameter}"</td>
      </tr>
      <tr>
        <td class="detail-parameter"><span class="bold">Руль:</span></td>
        <td class="detail-value">${bicycle.handlebar}</td>
      </tr>     
      <tr>
        <td class="detail-parameter"><span class="bold">Седло:</span></td>
        <td class="detail-value">${bicycle.saddle}</td>
      </tr>
      <tr>
        <td class="detail-parameter"><span class="bold">Тормоза:</span></td>
        <td class="detail-value">${bicycle.brakes}</td>
      </tr>
      <tr>
        <td class="detail-parameter"><span class="bold">Педали:</span></td>
        <td class="detail-value">${bicycle.pedals}</td>
      </tr>
      <tr>
        <td class="detail-parameter"><span class="bold">Покрышки:</span></td>
        <td class="detail-value">${bicycle.tires}</td>
      </tr>
    </tbody>
  </table>

  <div class="detail-category">Трансмиссия</div>
  <table class="detail-parameters">
    <tbody>
      <tr>
        <td class="detail-parameter"><span class="bold">Количество скоростей:</span></td>
        <td class="detail-value">${bicycle.ratesNumber}</td>
      </tr>
      <tr>
        <td class="detail-parameter"><span class="bold">Передний переключатель:</span></td>
        <td class="detail-value">${bicycle.frontDerailer}</td>
      </tr>
      <tr>
        <td class="detail-parameter"><span class="bold">Задний переключатель:</span></td>
        <td class="detail-value">${bicycle.rearDerailer}</td>
      </tr>     
      <tr>
        <td class="detail-parameter"><span class="bold">Система:</span></td>
        <td class="detail-value">${bicycle.cranckset}</td>
      </tr>
      <tr>
        <td class="detail-parameter"><span class="bold">Кассета:</span></td>
        <td class="detail-value">${bicycle.cassette}</td>
      </tr>
      <tr>
        <td class="detail-parameter"><span class="bold">Манетки:</span></td>
        <td class="detail-value">${bicycle.shifters}</td>
      </tr>
      <tr>
        <td class="detail-parameter"><span class="bold">Цепь:</span></td>
        <td class="detail-value">${bicycle.chain}</td>
      </tr>
    </tbody>
  </table>

  <table class="detail-parameters">
    <tbody>
      <tr>
        <td class="detail-parameter detail-cost">
          <span class="bold">Цена: </span>${bicycle.price} у. е.
        </td>
        <td class="detail-value">
          <div class="button order-button">
            <a class="button order-button" href="${pageContext.request.contextPath}/catalog/${bicycle.id}/order">Заказать!</a> 
          </div>
        </td>
      </tr>
    </tbody>
  </table>
</div>
