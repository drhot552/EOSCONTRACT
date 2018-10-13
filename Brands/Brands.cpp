#include <eosiolib/eosio.hpp>
#include <eosiolib/print.hpp>
using namespace eosio;
using namespace std;
class Brands : public eosio::contract
{
    public:
        using contract::contract;
        /// @abi table
        struct brands
        {
            uint64_t id;
            account_name to;
            account_name from;
            string brands_name;
            string brands_num;
            uint64_t primary_key() const {return id;}
            EOSLIB_SERIALIZE(brands,(id)(to)(from)(brands_name)(brands_num))
        };
        typedef multi_index<N(brands),brands> _brands;
        /// @abi action
        void create(uint64_t id, account_name user, account_name _from, string _brands_name, string _brands_num)
        {
             _brands tables(_self,_self);

            auto iter=tables.find(id);
            if(iter==tables.end())
            {
                print("need insert\t");
                tables.emplace(_self,[&](auto& brands)
                {
                    brands.id = id;
                    brands.to = user;
                    brands.from = _from;
                    brands.brands_num = _brands_num;
                    brands.brands_name = _brands_name;
                });
            }
            else
            {
                uint64_t getuser;
                getuser=iter->to;
            }
        }
        //delete
        void del(uint64_t id, string _brands_num)
        {
            _brands tables(_self,_self);
            auto iter=tables.find(id);
            if(iter!=tables.end())
            {
                tables.erase(iter);
            }
        }
        //edit (product edit)
        void edit(uint64_t id, account_name org, string _brands_name, string _brands_num)
        {
             _brands tables(_self,_self);
            auto iter=tables.find(id);
            if(iter!=tables.end())
            {
                tables.modify(iter,_self,[&](auto& edit_table)
                {
                    edit_table.brands_name = _brands_name;
                    edit_table.brands_num = _brands_num;
                });
            }
        }
};
EOSIO_ABI(Brands,(create)(del)(edit))

