-- usage example
-- set @psv = passport_code_verification(2); select @psv;

delimiter endfunc
create function passport_code_verification(
    _code int)
    returns varchar(25)
begin
    declare result varchar(25);
    declare _passport_code varchar(25);
    select passport_code from products
        where code = _code into _passport_code;
    select _passport_code
        regexp '^[A-Z]{2}-{1}[0-9]{8}' into result;
    return result;
end;
endfunc
delimiter ;
