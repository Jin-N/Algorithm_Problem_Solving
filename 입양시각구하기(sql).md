[문제링크](https://programmers.co.kr/learn/courses/30/lessons/59413)

SQL 문제를 풀어보았다.

백엔드 개발자를 희망하는 사람으로서, SQL 문법에도 능숙할 필요를 느낀다.

좀 더 구체적인 이유로는, programmers에서 진행하는 백엔드 개발자 dev-matching에서 SQL문제도 내기 때문이다.

문제 자체는 분명 어렵지 않는데, 당황스럽게도...

##### 0부터 24까지의 정보를 쭉 나열할 때, 몇몇 숫자는 그것을 속성값으로 갖는 행이 하나도 없을 경우, 어떻게 그 숫자에서 count 값이 0으로 표현되게 할 수 있는지 모르고 있었다는 사실을 깨달았다.

분명 이것을 표현할 수 있는 문법이 SQL에 있을 테지만, 

문제는 내가 공부한 입문서적(모두의 SQL)에는 나와있지 않다는 사실이다.

이가 없으면 잇몸이다. row_number 함수를 이용해 등수를 매겨 그 숫자를 활용하는 방법을 썼다.

불필요한 연산이 무지막지하게 들어가 있겠지만 어찌저찌 풀기는 했다.



### 정답

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

