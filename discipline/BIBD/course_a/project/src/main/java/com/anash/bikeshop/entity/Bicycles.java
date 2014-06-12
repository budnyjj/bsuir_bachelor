package com.anash.bikeshop.entity;

import com.anash.bikeshop.entity.enums.BicycleSize;
import com.anash.bikeshop.entity.enums.FrameMaterial;
import org.hibernate.annotations.GenericGenerator;
import org.hibernate.validator.constraints.Range;

import javax.persistence.*;
import java.io.Serializable;

@Entity
@Table(name = "bicycles")
public class Bicycles implements Serializable {

    @Id
    @GeneratedValue(generator = "increment")
    @GenericGenerator(name = "increment", strategy = "increment")
    @Column(name = "id", length = 6, nullable = false)
    private long id;

    @Column(name = "product_name", nullable = false)
    private String productName;

    @Column(name = "manufacturer", nullable = false)
    private String manufacturer;

    @Column(name = "type")
    private String type;

    @Range(min = 1900, max = 2500)
    @Column(name = "year")
    private Integer year;

    @Column(name = "color")
    private String color;

    @Enumerated(EnumType.STRING)
    @Column(name = "bicycle_size", nullable = false)
    private BicycleSize size;

    @Range(min = 1, max = 50)
    @Column(name = "rates_number")
    private Byte ratesNumber;

    @Column(name = "weight")
    private Double weight;

    @Column(name = "brakes")
    private String brakes;

    @Range(min = 1, max = 50)
    @Column(name = "wheels_diameter")
    private Byte wheelsDiameter;

    @Enumerated(EnumType.STRING)
    @Column(name = "frame_materials")
    private FrameMaterial frameMaterial;

    @Column(name = "fork")
    private String fork;

    @Column(name = "lockout")
    private Boolean lockout;

    @Range(max = 300)
    @Column(name = "fork_move")
    private Integer forkMove;

    @Column(name = "front_derailer")
    private String frontDerailer;

    @Column(name = "rear_derailer")
    private String rearDerailer;

    @Column(name = "cranckset")
    private String cranckset;

    @Column(name = "cassette")
    private String cassette;

    @Column(name = "saddle")
    private String saddle;

    @Column(name = "shifters")
    private String shifters;

    @Column(name = "chain")
    private String chain;

    @Column(name = "handlebar")
    private String handlebar;

    @Column(name = "pedals")
    private String pedals;

    @Column(name = "tires")
    private String tires;

    @Column(name = "guarantee")
    private String guarantee;

    @Column(name = "photo_path")
    private String photoPath;

    @Column(name = "price")
    private Double price;

    public long getId() {
        return id;
    }

    public String getProductName() {
        return productName;
    }

    public void setProductName(String productName) {
        this.productName = productName;
    }

    public String getManufacturer() {
        return manufacturer;
    }

    public void setManufacturer(String manufacturer) {
        this.manufacturer = manufacturer;
    }

    public String getType() {
        return type;
    }

    public void setType(String type) {
        this.type = type;
    }

    public Integer getYear() {
        return year;
    }

    public void setYear(Integer year) {
        this.year = year;
    }

    public String getColor() {
        return color;
    }

    public void setColor(String color) {
        this.color = color;
    }

    public BicycleSize getSize() {
        return size;
    }

    public void setSize(BicycleSize size) {
        this.size = size;
    }

    public Byte getRatesNumber() {
        return ratesNumber;
    }

    public void setRatesNumber(Byte ratesNumber) {
        this.ratesNumber = ratesNumber;
    }

    public Double getWeight() {
        return weight;
    }

    public void setWeight(Double weight) {
        this.weight = weight;
    }

    public String getBrakes() {
        return brakes;
    }

    public void setBrakes(String brakes) {
        this.brakes = brakes;
    }

    public Byte getWheelsDiameter() {
        return wheelsDiameter;
    }

    public void setWheelsDiameter(Byte wheelsDiameter) {
        this.wheelsDiameter = wheelsDiameter;
    }

    public FrameMaterial getFrameMaterial() {
        return frameMaterial;
    }

    public void setFrameMaterial(FrameMaterial frameMaterial) {
        this.frameMaterial = frameMaterial;
    }

    public String getFork() {
        return fork;
    }

    public void setFork(String fork) {
        this.fork = fork;
    }

    public Boolean getLockout() {
        return lockout;
    }

    public void setLockout(Boolean lockout) {
        this.lockout = lockout;
    }

    public Integer getForkMove() {
        return forkMove;
    }

    public void setForkMove(Integer forkMove) {
        this.forkMove = forkMove;
    }

    public String getFrontDerailer() {
        return frontDerailer;
    }

    public void setFrontDerailer(String frontDerailer) {
        this.frontDerailer = frontDerailer;
    }

    public String getRearDerailer() {
        return rearDerailer;
    }

    public void setRearDerailer(String rearDerailer) {
        this.rearDerailer = rearDerailer;
    }

    public String getCranckset() {
        return cranckset;
    }

    public void setCranckset(String cranckset) {
        this.cranckset = cranckset;
    }

    public String getCassette() {
        return cassette;
    }

    public void setCassette(String cassette) {
        this.cassette = cassette;
    }

    public String getSaddle() {
        return saddle;
    }

    public void setSaddle(String saddle) {
        this.saddle = saddle;
    }

    public String getShifters() {
        return shifters;
    }

    public void setShifters(String shifters) {
        this.shifters = shifters;
    }

    public String getChain() {
        return chain;
    }

    public void setChain(String chain) {
        this.chain = chain;
    }

    public String getHandlebar() {
        return handlebar;
    }

    public void setHandlebar(String handlebar) {
        this.handlebar = handlebar;
    }

    public String getPedals() {
        return pedals;
    }

    public void setPedals(String pedals) {
        this.pedals = pedals;
    }

    public String getTires() {
        return tires;
    }

    public void setTires(String tires) {
        this.tires = tires;
    }

    public String getGuarantee() {
        return guarantee;
    }

    public void setGuarantee(String guarantee) {
        this.guarantee = guarantee;
    }

    public String getPhotoPath() {
        return photoPath;
    }

    public void setPhotoPath(String photoPath) {
        this.photoPath = photoPath;
    }

    public Double getPrice() {
        return price;
    }

    public void setPrice(Double price) {
        this.price = price;
    }
}
