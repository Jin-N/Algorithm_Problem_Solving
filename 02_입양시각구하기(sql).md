```sql
select HOUR, count(*)-1
from (
    select animal_id, 
           animal_type, 
           to_number(to_char(datetime, 'HH24')) HOUR,
           name, 
           sex_upon_outcome
    from animal_outs

    UNION ALL
    -- 0부터 23까지의 숫자를 얻기 위해 뻘짓을 해야한다...

    select *
    from (
        -- where 절에서 별칭을 쓰기 위해 서브쿼리로 묶었다.
        select animal_id, 
               animal_type, 
               row_number() over(order by datetime) - 1 등수, 
               name, 
               sex_upon_outcome
        from animal_outs
        )
    where 등수 <= 23
    )
where HOUR <= 23
group by HOUR
order by HOUR
```

