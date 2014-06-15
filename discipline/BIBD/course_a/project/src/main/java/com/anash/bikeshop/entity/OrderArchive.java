package com.anash.bikeshop.entity;

import javax.persistence.*;
import javax.validation.constraints.NotNull;
import java.io.Serializable;
import java.util.Date;

@Entity
@Table(name = "orders_archive")
public class OrderArchive implements Serializable {
    @Id
    @GeneratedValue(strategy = GenerationType.AUTO)
    private Integer id;

    @NotNull
    @ManyToOne(cascade = CascadeType.ALL)
    @JoinColumn(name = "bicycle_id", nullable = false)
    private Bicycle bicycle;

    @NotNull
    @Column(name = "goods_cost", nullable = false)
    private Double goodsCost;

    @NotNull
    @Temporal(TemporalType.DATE)
    @Column(name = "order_date", nullable = false)
    private Date orderDate;

    @NotNull
    @ManyToOne(cascade = CascadeType.ALL)
    @JoinColumn(name = "user_id", nullable = false)
    private User user;

    public Integer getId() {
        return id;
    }

    public void setId(Integer id) {
        this.id = id;
    }

    public Bicycle getBicycle() {
        return bicycle;
    }

    public void setBicycle(Bicycle bicycle) {
        this.bicycle = bicycle;
    }

    public Double getGoodsCost() {
        return goodsCost;
    }

    public void setGoodsCost(Double goodsCost) {
        this.goodsCost = goodsCost;
    }

    public Date getOrderDate() {
        return orderDate;
    }

    public void setOrderDate(Date orderDate) {
        this.orderDate = orderDate;
    }

    public User getUser() {
        return user;
    }

    public void setUser(User user) {
        this.user = user;
    }
}
