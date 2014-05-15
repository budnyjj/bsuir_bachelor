-- usage example
-- set @addr = address_verification(0); select @addr;

delimiter endfunc
create function address_verification(
    _code int)
    returns varchar(25)
begin
    declare result varchar(25);
    declare _address varchar(25);
    select supplier_address from products
        where code = _code into _address;
    select _address
        regexp '^(Minsk|Grodno)$' into result;
    return result;
end;
endfunc
delimiter ;
