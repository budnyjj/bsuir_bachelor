-- usage example
-- select @avg_price = average_price('milk');

delimiter endfunc
create function average_price(
    _title varchar(25))
    returns float
begin
    declare avg_price float;
    select avg(price) from 
        warehouse where title = _title into avg_price;
    return avg_price;
end;
endfunc
delimiter ;