package com.example.pr_idi.mydatabaseexample.persistence;

public class CoinModel {
    private String currency;
    private Float value;
    private Integer year;
    private String country;
    private String description;

    public CoinModel() {
    }

    public String getCurrency() {
        return currency;
    }

    public Float getValue() {
        return value;
    }

    public Integer getYear() {
        return year;
    }

    public String getCountry() {
        return country;
    }

    public String getDescription() {
        return description;
    }

    public void setCurrency(String currency) {
        this.currency = currency;
    }

    public void setValue(Float value) {
        this.value = value;
    }

    public void setYear(Integer year) {
        this.year = year;
    }

    public void setCountry(String country) {
        this.country = country;
    }

    public void setDescription(String description) {
        this.description = description;
    }
}
